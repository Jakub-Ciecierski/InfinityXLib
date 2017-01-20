#include "physics/rigid_body.h"

#include <physics/collision/collision_shape.h>

#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btDefaultMotionState.h>

namespace ifx{

RigidBody::RigidBody(std::shared_ptr<CollisionShape> collision_shape,
                     float mass) :
        GameComponent(GameComponentType::PHYSICS),
        collision_shape_(collision_shape),
        mass_(mass){
    Init();
}

RigidBody::RigidBody() :
        GameComponent(GameComponentType::PHYSICS),
        collision_shape_(nullptr),
        mass_(0){}

RigidBody::~RigidBody(){}

glm::vec3 RigidBody::GetLinearVelocity(){
    auto vel = rigid_body_bt_->getLinearVelocity();

    return glm::vec3(vel.x(), vel.y(), vel.z());
}

void RigidBody::SetLinearVelocity(const glm::vec3& vel){
    auto vel_bt = btVector3(vel.x, vel.y, vel.z);
    rigid_body_bt_->setLinearVelocity(vel_bt);
}

void RigidBody::Init(){
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
    rigid_body_bt_ = std::shared_ptr<btRigidBody>(new btRigidBody(bt_info));
}

}