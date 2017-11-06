#include "physics/collision/shapes/static_plane_shape.h"

#include <BulletCollision/CollisionShapes/btStaticPlaneShape.h>
#include <physics/rigid_body/impl/rigid_body_impl.h>

namespace ifx {

StaticPlaneShape::StaticPlaneShape(const glm::vec3 &normal,
                                   float plane_constant) :
    normal_(normal),
    plane_constant_(plane_constant) {}

void StaticPlaneShape::InitImpl(RigidBodyImpl *rigid_body_impl) {
    rigid_body_impl->InitCollisionShape(this);
}

}