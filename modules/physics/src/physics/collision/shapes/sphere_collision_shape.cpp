#include "physics/collision/shapes/sphere_collision_shape.h"

#include "physics/rigid_body/impl/rigid_body_impl.h"

namespace ifx {

SphereCollisionShape::SphereCollisionShape(float radius) :
        CollisionShape(CollisionShapeType::Sphere),
        radius_(radius){}

void SphereCollisionShape::InitImpl(RigidBodyImpl *rigid_body_impl) {
    rigid_body_impl->InitCollisionShape(this);
}

}