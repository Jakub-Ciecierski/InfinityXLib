#include "physics/collision/shapes/box_collision_shape.h"

#include <BulletCollision/CollisionShapes/btBoxShape.h>

namespace ifx{

BoxCollisionShape::BoxCollisionShape(const glm::vec3 dim){
    collision_shape_bt_= std::shared_ptr<btBoxShape>(new btBoxShape(
            btVector3(dim.x, dim.y, dim.z)));
}

BoxCollisionShape::~BoxCollisionShape(){}

}