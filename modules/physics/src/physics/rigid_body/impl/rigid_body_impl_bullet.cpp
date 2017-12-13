#include "physics/rigid_body/impl/rigid_body_impl_bullet.h"

#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletCollision/CollisionShapes/btStaticPlaneShape.h>
#include <LinearMath/btDefaultMotionState.h>

#include <physics/collision/collision_shape.h>
#include <physics/collision/shapes/static_plane_shape.h>
#include <physics/collision/shapes/box_collision_shape.h>
#include <physics/collision/shapes/sphere_collision_shape.h>

#include <BulletCollision/CollisionShapes/btSphereShape.h>

namespace ifx {

void *RigidBodyImplBullet::GetNativeRigidBody() {
    return (void *) rigid_body_bt_.get();
}

void RigidBodyImplBullet::InitImpl(
    std::shared_ptr<CollisionShape> collision_shape,
    float mass,
    const PhysicsMaterial& physics_material) {
    ifx_collision_shape_ = collision_shape;
    physics_material_ = physics_material;
    mass_ = mass;

    collision_shape->InitImpl(this);
    if (!collision_shape_bt_)
        throw std::invalid_argument("collision_shape_bt_ failed to Init");

    bool isDynamic = (mass != 0.f);
    btVector3 localInertia(0, 0, 0);
    if (isDynamic) {
        collision_shape_bt_->
            calculateLocalInertia(mass, localInertia);
    }

    btRigidBody::btRigidBodyConstructionInfo bt_info(
        mass, nullptr,
        collision_shape_bt_.get(), localInertia);

    rigid_body_bt_ = std::unique_ptr<btRigidBody>(new btRigidBody(bt_info));
}

void RigidBodyImplBullet::InitCollisionShape(const StaticPlaneShape *shape) {
    const auto &normal = shape->normal();
    collision_shape_bt_ = std::shared_ptr<btStaticPlaneShape>(
        new btStaticPlaneShape(
            btVector3(normal.x, normal.y, normal.z),
            shape->plane_constant()));
}

void RigidBodyImplBullet::InitCollisionShape(const BoxCollisionShape *shape) {
    const auto &dim = shape->dimension();
    collision_shape_bt_ = std::shared_ptr<btBoxShape>(new btBoxShape(
        btVector3(dim.x, dim.y, dim.z)));
}

void RigidBodyImplBullet::InitCollisionShape(const SphereCollisionShape *shape){
    collision_shape_bt_ = std::make_shared<btSphereShape>(shape->radius());
}

void RigidBodyImplBullet::InitCollisionShape(const MeshCollisionShape *shape){
    throw std::invalid_argument(
            "RigidBodyImplBullet::InitCollisionShape Not Implemented");
}

void RigidBodyImplBullet::SetCollisionShapeScale(const glm::vec3 &scale) {
    if (ifx_collision_shape_->scale() == scale) {
        return;
    }
    ifx_collision_shape_->scale(scale);

    collision_shape_bt_->setLocalScaling(btVector3(scale.x,
                                                   scale.y,
                                                   scale.z));
}

bool RigidBodyImplBullet::IsDynamic() {
    return rigid_body_bt_->getInvMass() != 0;
}

void RigidBodyImplBullet::SetMass(float mass){
    throw std::invalid_argument("RigidBodyImplBullet::SetMass Not Implemented");
}

void RigidBodyImplBullet::SetPhysicsMaterial(
        const PhysicsMaterial& physics_material){
    throw std::invalid_argument(
            "RigidBodyImplBullet::SetPhysicsMaterial Not Implemented");
}

void RigidBodyImplBullet::SetIsKinematic(bool is_kinematic){
    throw std::invalid_argument(
        "RigidBodyImplBullet::SetIsKinematic Not Implemented");
}

void RigidBodyImplBullet::SetUserData(void* user_data_){
    throw std::invalid_argument(
        "RigidBodyImplBullet::SetUserData Not Implemented");
}

void RigidBodyImplBullet::SetGlobalTransform(const glm::vec3 &position,
                                             const glm::quat &rotation) {
    btQuaternion bt_quat(rotation.x,
                         rotation.y,
                         rotation.z,
                         rotation.w);
    auto transform = rigid_body_bt_->getWorldTransform();

    transform.setOrigin(
        btVector3(position.x, position.y, position.z));
    transform.setRotation(bt_quat);

    rigid_body_bt_->setWorldTransform(transform);
}

void RigidBodyImplBullet::SetVelocity(const glm::vec3& velocity){
    rigid_body_bt_->setLinearVelocity(btVector3{velocity.x,
                                                velocity.y,
                                                velocity.z});
}

glm::vec3 RigidBodyImplBullet::GetVelocity(){
    const auto& velocity = rigid_body_bt_->getLinearVelocity();
    return glm::vec3(velocity.x(), velocity.y(), velocity.z());
}

}