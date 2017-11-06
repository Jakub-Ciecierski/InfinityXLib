#include "physics/collision/collision_shape.h"

namespace ifx {

CollisionShape::CollisionShape(CollisionShapeType type) :
        scale_(glm::vec3(1, 1, 1)),
        type_(type){}

}