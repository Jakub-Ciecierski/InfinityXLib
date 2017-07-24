#include "physics/simulations/physx_physics_simulation.h"

#include <physics/rigid_body.h>
#include <physics/impl/rigid_body_impl.h>

#define _DEBUG
#include <PxPhysicsAPI.h>

#include <common/unique_ptr.h>
#include <physics/impl/rigid_body_impl_physx.h>

namespace ifx {

PhysxPhysicsSimulation::PhysxPhysicsSimulation(
        physx::PxPhysics *px_physics,
        physx::PxPvd *px_pvd,
        physx::PxPvdTransport *px_pvd_transport,
        physx::PxFoundation *px_foundation,
        std::unique_ptr<physx::PxAllocatorCallback> px_allocator_callback,
        std::unique_ptr<physx::PxErrorCallback> px_error_callback,
        physx::PxDefaultCpuDispatcher *px_dispatcher,
        physx::PxScene *px_scene) :
        px_physics_((px_physics)),
        px_pvd_((px_pvd)),
        px_pvd_transport_((px_pvd_transport)),
        px_foundation_((px_foundation)),
        px_allocator_callback_(std::move(px_allocator_callback)),
        px_error_callback_(std::move(px_error_callback)),
        px_dispatcher_((px_dispatcher)),
        px_scene_((px_scene)) {}

PhysxPhysicsSimulation::~PhysxPhysicsSimulation() {
    px_scene_->release();
    px_dispatcher_->release();
    px_physics_->release();
    px_pvd_->release();
    px_pvd_transport_->release();
    px_foundation_->release();
}

void PhysxPhysicsSimulation::Update(float time_delta) {
    if(!is_running_)
        return;

    PX_UNUSED(false);

    SynchronizeRigidBodiesTransform();

    px_scene_->simulate(time_delta);
    px_scene_->fetchResults(true);

    SynchronizeGameObjectsTransform();
}

void PhysxPhysicsSimulation::Add(std::shared_ptr<RigidBody> rigid_body) {
    PhysicsSimulation::Add(rigid_body);
    auto px_actor = (physx::PxRigidActor*)rigid_body->GetNativeRigidBody();
    px_scene_->addActor(*px_actor);
}

bool PhysxPhysicsSimulation::Remove(std::shared_ptr<RigidBody> rigid_body) {
    bool ret = PhysicsSimulation::Remove(rigid_body);

    auto px_actor = (physx::PxRigidActor*)rigid_body->GetNativeRigidBody();

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
    return ifx::make_unique<RigidBodyImplPhysx>(px_physics_);
}

void PhysxPhysicsSimulation::SynchronizeRigidBodiesTransform(){
    for(auto& rigid_body : rigid_bodies_){
        auto parent = rigid_body->movable_parent();
        if(!parent)
            continue;
        auto px_rigid_actor
                = (physx::PxRigidActor*)rigid_body->GetNativeRigidBody();

        auto& ifx_position = rigid_body->getPosition();
        auto& ifx_rotation = rigid_body->getRotation();
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

void PhysxPhysicsSimulation::SynchronizeGameObjectsTransform(){
    for(auto& rigid_body : rigid_bodies_){
        auto parent = rigid_body->movable_parent();
        if(!parent)
            continue;
        auto px_rigid_actor
                = (physx::PxRigidActor*)rigid_body->GetNativeRigidBody();
        const auto& px_transform = px_rigid_actor->getGlobalPose();
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