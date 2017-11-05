#include "physics/collision/shapes/box_collision_shape.h"

#include <BulletCollision/CollisionShapes/btBoxShape.h>

#include <physics/rigid_body/impl/rigid_body_impl.h>

namespace ifx {

BoxCollisionShape::BoxCollisionShape(const glm::vec3 &dim) :
    dimension_(dim) {}

BoxCollisionShape::~BoxCollisionShape() {}

void BoxCollisionShape::InitImpl(RigidBodyImpl *rigid_body_impl) {
    rigid_body_impl->InitCollisionShape(this);
}

}