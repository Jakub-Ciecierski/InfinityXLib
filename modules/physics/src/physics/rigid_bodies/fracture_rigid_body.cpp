#include "physics/rigid_bodies/fracture_rigid_body.h"
#include <physics/bullet_extensions/btFractureBody.h>
#include <physics/collision/collision_shape.h>
#include <physics/simulations/bullet_physics_simulation.h>

#include <LinearMath/btDefaultMotionState.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>

namespace ifx{

FractureRigidBody::FractureRigidBody(
        std::shared_ptr<CollisionShape> collision_shape, float mass,
        std::shared_ptr<BulletPhysicsSimulation> simulation)
        : RigidBody(collision_shape, mass),
          simulation_(simulation){
    Init();
}

FractureRigidBody::FractureRigidBody(
        std::shared_ptr<btFractureBody> fracture_body_bt){
    rigid_body_bt_ = fracture_body_bt;
}

FractureRigidBody::~FractureRigidBody(){}

void FractureRigidBody::Init(){
    motion_state_bt_  = std::shared_ptr<btDefaultMotionState>(
            new btDefaultMotionState());

    bool isDynamic = (mass_ != 0.f);
    btVector3 localInertia(0, 0, 0);
    if (isDynamic){
        collision_shape_->collision_shape_bt()->
                calculateLocalInertia(mass_, localInertia);
    }

    btRigidBody::btRigidBodyConstructionInfo bt_info(
            mass_, nullptr,
            collision_shape_->collision_shape_bt().get(), localInertia);
    rigid_body_bt_ = std::shared_ptr<btFractureBody>(
            new btFractureBody(bt_info,
                               simulation_->dynamics_world_bt().get()));
}

}