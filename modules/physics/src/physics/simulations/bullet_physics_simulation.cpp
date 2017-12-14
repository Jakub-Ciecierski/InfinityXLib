#include "physics/simulations/bullet_physics_simulation.h"

#include "physics/rigid_body/rigid_body.h"
#include <physics/soft_body/simulation/soft_body_fem_simulation.h>
#include <physics/rigid_body/impl/rigid_body_impl.h>
#include <physics/rigid_body/impl/rigid_body_impl_bullet.h>

#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>

#include "RTFEM/GPU/LinearSolver/GPULULinearSolver.cuh"

#include <iostream>

namespace ifx {

BulletPhysicsSimulation::BulletPhysicsSimulation(
    std::shared_ptr<PhysicsContext> physics_context,
    const BulletPhysicsSimulationCreateParams &params) :
    PhysicsSimulation(physics_context),
    broadphase_(params.broadphase),
    dispatcher_(params.dispatcher),
    solver_(params.solver),
    collision_configuration_(params.collision_configuration),
    dynamics_world_(params.dynamics_world) {
    SetGravity(glm::vec3(0, -9.81, 0));
}

bool BulletPhysicsSimulation::Terminate() {
    return true;
}

void BulletPhysicsSimulation::Add(std::shared_ptr<RigidBody> rigid_body) {
    PhysicsSimulation::Add(rigid_body);

    dynamics_world_->addRigidBody(
        (btRigidBody *) rigid_body->GetNativeRigidBody());
}

bool BulletPhysicsSimulation::Remove(std::shared_ptr<RigidBody> rigid_body) {
    bool result = PhysicsSimulation::Remove(rigid_body);
    dynamics_world_->removeRigidBody(
        (btRigidBody *) rigid_body->GetNativeRigidBody());

    return result;
}

std::unique_ptr<RigidBodyImpl>
BulletPhysicsSimulation::CreateRigidBodyImpl() {
    return std::unique_ptr<RigidBodyImplBullet>(new RigidBodyImplBullet());
}

void BulletPhysicsSimulation::UpdateFixedContent() {
    PhysicsSimulation::UpdateFixedContent();

    SynchronizeRigidBodiesTransform();
    dynamics_world_->stepSimulation(update_time_delta_.time_delta);
    SynchronizeGameObjectsTransform();
}

void BulletPhysicsSimulation::SetGravity(const glm::vec3 &g) {
    dynamics_world_->setGravity(btVector3(g.x, g.y, g.z));
}

glm::vec3 BulletPhysicsSimulation::GetGravity() {
    auto gravity = dynamics_world_->getGravity();

    return glm::vec3(gravity.x(), gravity.y(), gravity.z());
}

void BulletPhysicsSimulation::AddImpulse() {}

void BulletPhysicsSimulation::SynchronizeRigidBodiesTransform() {
    for (auto &rigid_body : rigid_bodies_) {
        auto parent = rigid_body->movable_parent();
        if (!parent)
            continue;

        auto &position = rigid_body->getPosition();
        auto &rotation = rigid_body->getRotation();
        glm::quat glm_quat(glm::radians(rotation));

        rigid_body->SetGlobalTransform(position, glm_quat);

        auto rigid_body_bt = (btRigidBody *) rigid_body->GetNativeRigidBody();

        // TODO
        rigid_body_bt->activate(true);
    }
}

void BulletPhysicsSimulation::SynchronizeGameObjectsTransform() {
    for (auto &rigid_body : rigid_bodies_) {
        auto parent = rigid_body->movable_parent();
        if (!parent)
            continue;
        auto rigid_body_bt = (btRigidBody *) rigid_body->GetNativeRigidBody();

        auto transform = rigid_body_bt->getWorldTransform();
        auto &origin = transform.getOrigin();
        auto rotation_quat = transform.getRotation();
        glm::quat glm_quat = glm::quat(rotation_quat.w(), rotation_quat.x(),
                                       rotation_quat.y(), rotation_quat.z());

        parent->moveTo(glm::vec3(origin.x(), origin.y(), origin.z()));
        parent->rotateTo(glm::degrees(glm::eulerAngles(glm_quat)));
    }
}

}