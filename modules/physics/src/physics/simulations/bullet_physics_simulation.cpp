#include "physics/simulations/bullet_physics_simulation.h"
#include <physics/rigid_body.h>

#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <iostream>

namespace ifx {

BulletPhysicsSimulation::BulletPhysicsSimulation(
        const BulletPhysicsSimulationCreateParams& params) :
        broadphase_(params.broadphase),
        dispatcher_(params.dispatcher),
        solver_(params.solver),
        collision_configuration_(params.collision_configuration),
        dynamics_world_(params.dynamics_world){
    SetGravity(glm::vec3(0,-9.81,0));
}

BulletPhysicsSimulation::~BulletPhysicsSimulation(){}

void BulletPhysicsSimulation::Add(std::shared_ptr<RigidBody> rigid_body){
    PhysicsSimulation::Add(rigid_body);
    dynamics_world_->addRigidBody(rigid_body->rigid_body_bt().get());
}

bool BulletPhysicsSimulation::Remove(std::shared_ptr<RigidBody> rigid_body){
    bool result = PhysicsSimulation::Remove(rigid_body);
    dynamics_world_->removeRigidBody(rigid_body->rigid_body_bt().get());

    return result;
}

void BulletPhysicsSimulation::Update(float time_delta){
    if(!is_running_)
        return;

    SynchronizeRigidBodiesTransform();
    dynamics_world_->stepSimulation(time_delta);
    SynchronizeGameObjectsTransform();
}

void BulletPhysicsSimulation::SetGravity(const glm::vec3& g){
    dynamics_world_->setGravity(btVector3(g.x, g.y, g.z));
}

glm::vec3 BulletPhysicsSimulation::GetGravity(){
    auto gravity = dynamics_world_->getGravity();

    return glm::vec3(gravity.x(), gravity.y(), gravity.z());
}

void BulletPhysicsSimulation::AddImpulse(){
    for(auto& rigid_body : rigid_bodies_){
        btVector3 impulse(0.1, 1.1, 0.1);
        rigid_body->rigid_body_bt()->applyCentralImpulse(impulse);
    }
}

void BulletPhysicsSimulation::SynchronizeRigidBodiesTransform(){
    for(auto& rigid_body : rigid_bodies_){
        auto parent = rigid_body->movable_parent();
        if(!parent)
            continue;

        auto transform = rigid_body->rigid_body_bt()->getWorldTransform();
        auto& position = rigid_body->getPosition();
        auto& rotation = rigid_body->getRotation();
        glm::quat glm_quat(glm::radians(rotation));
        btQuaternion bt_quat(glm_quat.x, glm_quat.y, glm_quat.z, glm_quat.w);
        transform.setOrigin(
                btVector3(position.x, position.y, position.z));
        transform.setRotation(bt_quat);

        rigid_body->rigid_body_bt()->setWorldTransform(transform);

        // TODO
        rigid_body->rigid_body_bt()->activate(true);
    }
}

void BulletPhysicsSimulation::SynchronizeGameObjectsTransform(){
    for(auto& rigid_body : rigid_bodies_){
        auto parent = rigid_body->movable_parent();
        if(!parent)
            continue;

        auto transform = rigid_body->rigid_body_bt()->getWorldTransform();
        auto& origin = transform.getOrigin();
        auto rotation_quat = transform.getRotation();
        glm::quat glm_quat = glm::quat(rotation_quat.w(), rotation_quat.x(),
                                       rotation_quat.y(), rotation_quat.z());

        parent->moveTo(glm::vec3(origin.x(), origin.y(), origin.z()));
        parent->rotateTo(glm::degrees(glm::eulerAngles(glm_quat)));
    }
}

}