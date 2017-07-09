#include "physics/impl/rigid_body_impl_bullet.h"

#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btDefaultMotionState.h>
#include <physics/collision/collision_shape.h>

namespace ifx {

RigidBodyImplBullet::RigidBodyImplBullet(){}

RigidBodyImplBullet::~RigidBodyImplBullet(){}

void* RigidBodyImplBullet::GetNativeRigidBody(){
    return (void*)rigid_body_bt_.get();
}

void RigidBodyImplBullet::InitImpl(
        std::shared_ptr<CollisionShape> collision_shape,
        float mass) {
    bool isDynamic = (mass != 0.f);
    btVector3 localInertia(0, 0, 0);
    if (isDynamic){
        collision_shape->collision_shape_bt()->
                calculateLocalInertia(mass, localInertia);
    }

    btRigidBody::btRigidBodyConstructionInfo bt_info(
            mass, nullptr,
            collision_shape->collision_shape_bt().get(), localInertia);

    rigid_body_bt_ = std::unique_ptr<btRigidBody>(new btRigidBody(bt_info));
}

}