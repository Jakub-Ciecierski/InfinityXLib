#ifndef PROJECT_STATIC_PLANE_SHAPE_H
#define PROJECT_STATIC_PLANE_SHAPE_H

#include <physics/collision/collision_shape.h>
#include <math/math_ifx.h>

namespace ifx {

class StaticPlaneShape  : public CollisionShape {
public:

    StaticPlaneShape(const glm::vec3& normal, float plane_constant);
    ~StaticPlaneShape();

private:
};
}

#endif //PROJECT_STATIC_PLANE_SHAPE_H
