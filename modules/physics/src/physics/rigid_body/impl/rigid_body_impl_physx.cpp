#include <physics/rigid_body/impl/rigid_body_impl_physx.h>

#include <physics/collision/shapes/static_plane_shape.h>
#include <physics/collision/shapes/box_collision_shape.h>
#include <physics/collision/collision_shape.h>
#include <physics/collision/shapes/sphere_collision_shape.h>

#define _DEBUG
#include <PxPhysicsAPI.h>
#include <iostream>

namespace ifx {
RigidBodyImplPhysx::RigidBodyImplPhysx(physx::PxPhysics *px_physics) :
    px_physics_(px_physics),
    px_rigid_actor_(nullptr),
    px_shape_(nullptr) {}

RigidBodyImplPhysx::~RigidBodyImplPhysx() {
}

void *RigidBodyImplPhysx::GetNativeRigidBody() {
    return (void *) px_rigid_actor_;
}

void RigidBodyImplPhysx::InitImpl(
    std::shared_ptr<CollisionShape> collision_shape,
    float mass,
    const PhysicsMaterial& physics_material) {
    collision_shape_ = collision_shape;
    mass_ = mass;
    physics_material_ = physics_material;

    px_material_ = px_physics_->createMaterial(
            physics_material_.static_friction,
            physics_material_.dynamic_friction,
            physics_material_.restitution);

    collision_shape->InitImpl(this);
    if (!px_shape_)
        throw std::invalid_argument("px_shape_ failed to Init");

    if (IsDynamic()) {
        px_rigid_actor_ = px_physics_->createRigidDynamic(
            physx::PxTransform(physx::PxIDENTITY::PxIdentity));
        physx::PxRigidDynamic
            *dynamic = (physx::PxRigidDynamic *) px_rigid_actor_;
        dynamic->setMass(mass_);
    } else {
        px_rigid_actor_ = px_physics_->createRigidStatic(
            physx::PxTransform(physx::PxIDENTITY::PxIdentity));
    }
    if (!px_rigid_actor_)
        throw std::invalid_argument("px_rigid_actor_ failed to Init");

    px_rigid_actor_->attachShape(*px_shape_);
}

void RigidBodyImplPhysx::InitCollisionShape(const StaticPlaneShape *shape) {
    const auto &n = shape->normal();
    auto d = shape->plane_constant();

    px_shape_
        = px_physics_->createShape(physx::PxPlaneGeometry(), *px_material_);
    px_shape_->setLocalPose(physx::PxTransformFromPlaneEquation(physx::PxPlane(
        n.x, n.y, n.z, d)));
}

void RigidBodyImplPhysx::InitCollisionShape(const BoxCollisionShape *shape) {
    const auto &dim = shape->dimension();

    px_shape_ = px_physics_->createShape(
        physx::PxBoxGeometry(dim.x, dim.y, dim.z),
        *px_material_);
}

void RigidBodyImplPhysx::InitCollisionShape(const SphereCollisionShape *shape) {
    px_shape_ = px_physics_->createShape(
            physx::PxSphereGeometry(shape->radius()),
            *px_material_);
}

void RigidBodyImplPhysx::InitCollisionShape(const MeshCollisionShape *shape) {

}

void RigidBodyImplPhysx::SetCollisionShapeScale(const glm::vec3 &scale) {
    if (collision_shape_->scale() == scale) {
        return;
    }
    collision_shape_->scale(scale);

    physx::PxBoxGeometry box;
    if (px_shape_->getBoxGeometry(box)) {
        const auto &dimensions
            = std::static_pointer_cast<BoxCollisionShape>(
                        collision_shape_)->dimension();

        px_rigid_actor_->detachShape(*px_shape_);

        px_shape_->setGeometry(physx::PxBoxGeometry(dimensions.x * scale.x,
                                                    dimensions.y * scale.y,
                                                    dimensions.z * scale.z));
        px_rigid_actor_->attachShape(*px_shape_);
    }

    physx::PxSphereGeometry sphere;
    if (px_shape_->getSphereGeometry(sphere)) {
        const auto &radius
                = std::static_pointer_cast<SphereCollisionShape>(
                        collision_shape_)->radius();
        px_rigid_actor_->detachShape(*px_shape_);
        px_shape_->setGeometry(physx::PxSphereGeometry(radius * scale.x));
        px_rigid_actor_->attachShape(*px_shape_);
    }
}

bool RigidBodyImplPhysx::IsDynamic() {
    return mass_ != 0;
}

void RigidBodyImplPhysx::SetMass(float mass){
    physx::PxRigidDynamic
            *dynamic = (physx::PxRigidDynamic *) px_rigid_actor_;
    dynamic->setMass(mass);
}

void RigidBodyImplPhysx::SetPhysicsMaterial(
        const PhysicsMaterial& physics_material){
    if(!px_material_){
        return;
    }
    px_material_->setDynamicFriction(physics_material.dynamic_friction);
    px_material_->setStaticFriction(physics_material.static_friction);
    px_material_->setRestitution(physics_material.restitution);
}

}
