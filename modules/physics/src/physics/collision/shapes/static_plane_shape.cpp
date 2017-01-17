#include "physics/collision/shapes/static_plane_shape.h"

#include <BulletCollision/CollisionShapes/btStaticPlaneShape.h>

namespace ifx {

StaticPlaneShape::StaticPlaneShape(const glm::vec3 &normal,
                                   float plane_constant){
    collision_shape_bt_ = std::shared_ptr<btStaticPlaneShape>(
            new btStaticPlaneShape(
                    btVector3(normal.x, normal.y, normal.z), plane_constant));
}

StaticPlaneShape::~StaticPlaneShape(){}

}