#include "physics/simulations/physx_physics_simulation.h"

#include "physics/rigid_body/rigid_body.h"
#include <physics/rigid_body/impl/rigid_body_impl.h>
#include <physics/soft_body/simulation/soft_body_fem_simulation.h>
#include <physics/rigid_body/impl/rigid_body_impl_physx.h>
#include <physics/context/physx_context.h>

#define _DEBUG
#include <PxPhysicsAPI.h>

#include <common/unique_ptr.h>

namespace ifx {

PhysxPhysicsSimulation::PhysxPhysicsSimulation(
    std::shared_ptr<PhysicsContext> physics_context,
    physx::PxDefaultCpuDispatcher *px_dispatcher,
    physx::PxScene *px_scene) :
    PhysicsSimulation(physics_context),
    px_dispatcher_((px_dispatcher)),
    px_scene_((px_scene)) {}

bool PhysxPhysicsSimulation::Terminate() {
    px_scene_->release();
    px_dispatcher_->release();

    return true;
}

void PhysxPhysicsSimulation::UpdateFixedContent() {
    PhysicsSimulation::UpdateFixedContent();

    if (!is_running_)
        return;

    PX_UNUSED(false);

    SynchronizeRigidBodiesTransform();

    px_scene_->simulate(update_time_delta_.time_delta);
    px_scene_->fetchResults(true);

    SynchronizeGameObjectsTransform();
}

void PhysxPhysicsSimulation::Add(std::shared_ptr<RigidBody> rigid_body) {
    PhysicsSimulation::Add(rigid_body);
    auto px_actor = (physx::PxRigidActor *) rigid_body->GetNativeRigidBody();
    px_scene_->addActor(*px_actor);
}

bool PhysxPhysicsSimulation::Remove(std::shared_ptr<RigidBody> rigid_body) {
    bool ret = PhysicsSimulation::Remove(rigid_body);

    auto px_actor = (physx::PxRigidActor *) rigid_body->GetNativeRigidBody();

    px_scene_->removeActor(*px_actor);
    px_actor->release();

    return ret;
}

void PhysxPhysicsSimulation::SetGravity(const glm::vec3 &g) {
    px_scene_->setGravity(physx::PxVec3(g.x, g.y, g.z));
}

glm::vec3 PhysxPhysicsSimulation::GetGravity() {
    auto px_gravity = px_scene_->getGravity();

    return glm::vec3(px_gravity.x, px_gravity.y, px_gravity.z);
}

void PhysxPhysicsSimulation::AddImpulse() {

}

std::unique_ptr<RigidBodyImpl> PhysxPhysicsSimulation::CreateRigidBodyImpl() {
    auto physx_context = std::dynamic_pointer_cast<PhysxContext>(
        physics_context_);
    return ifx::make_unique<RigidBodyImplPhysx>(physx_context->px_physics());
}

void PhysxPhysicsSimulation::SynchronizeRigidBodiesTransform() {
    for (auto &rigid_body : rigid_bodies_) {
        auto parent = rigid_body->movable_parent();
        if (!parent)
            continue;
        auto px_rigid_actor
            = (physx::PxRigidActor *) rigid_body->GetNativeRigidBody();

        auto &ifx_position = rigid_body->getPosition();
        auto &ifx_rotation = rigid_body->getRotation();
        glm::quat ifx_quat(glm::radians(ifx_rotation));

        physx::PxTransform px_transform;
        px_transform.p = physx::PxVec3(ifx_position.x,
                                       ifx_position.y,
                                       ifx_position.z);
        px_transform.q = physx::PxQuat(ifx_quat.x, ifx_quat.y, ifx_quat.z,
                                       ifx_quat.w);

        px_rigid_actor->setGlobalPose(px_transform);
    }
}

void PhysxPhysicsSimulation::SynchronizeGameObjectsTransform() {
    for (auto &rigid_body : rigid_bodies_) {
        auto parent = rigid_body->movable_parent();
        if (!parent)
            continue;
        auto px_rigid_actor
            = (physx::PxRigidActor *) rigid_body->GetNativeRigidBody();
        const auto &px_transform = px_rigid_actor->getGlobalPose();
        glm::quat ifx_quat = glm::quat(px_transform.q.w,
                                       px_transform.q.x,
                                       px_transform.q.y,
                                       px_transform.q.z);
        parent->moveTo(glm::vec3(px_transform.p.x,
                                 px_transform.p.y,
                                 px_transform.p.z));
        parent->rotateTo(glm::degrees(glm::eulerAngles(ifx_quat)));
    }
}

}