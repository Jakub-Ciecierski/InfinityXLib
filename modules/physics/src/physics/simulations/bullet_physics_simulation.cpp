#include "physics/simulations/bullet_physics_simulation.h"
#include <physics/rigid_body.h>

#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <iostream>
#include <math/print_math.h>

namespace ifx {

BulletPhysicsSimulation::BulletPhysicsSimulation() :
        broadphase_(nullptr),
        dispatcher_(nullptr),
        solver_(nullptr),
        collision_configuration_(nullptr),
        dynamics_world_(nullptr){
    Init();
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
/*
        transform = rigid_body->rigid_body_bt()->getWorldTransform();
        std::cout
        << transform.getOrigin().x() << ", "
        << transform.getOrigin().y() << ", "
        << transform.getOrigin().z() << std::endl;*/
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
/*
        std::cout
        << transform.getOrigin().x() << ", "
        << transform.getOrigin().y() << ", "
        << transform.getOrigin().z() << std::endl;*/

        parent->moveTo(glm::vec3(origin.x(), origin.y(), origin.z()));
        parent->rotateTo(glm::degrees(glm::eulerAngles(glm_quat)));
    }
}

void BulletPhysicsSimulation::Init(){
    InitEmptyDynamicsWorld();
}

void BulletPhysicsSimulation::InitEmptyDynamicsWorld(){
    collision_configuration_
            = std::shared_ptr<btDefaultCollisionConfiguration>(
            new btDefaultCollisionConfiguration());

    dispatcher_ = std::shared_ptr<btCollisionDispatcher>(
            new btCollisionDispatcher(collision_configuration_.get()));

    broadphase_ = std::shared_ptr<btDbvtBroadphase>(new btDbvtBroadphase());

    solver_ = std::shared_ptr<btSequentialImpulseConstraintSolver>(
            new btSequentialImpulseConstraintSolver());
    dynamics_world_ = std::shared_ptr<btDiscreteDynamicsWorld>(
            new btDiscreteDynamicsWorld(dispatcher_.get(),
                                        broadphase_.get(),
                                        solver_.get(),
                                        collision_configuration_.get()));


    SetGravity(glm::vec3(0, -2.21,0));
    //SetGravity(glm::vec3(0,-9.81,0));
}

}