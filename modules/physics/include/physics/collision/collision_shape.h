#ifndef PROJECT_COLLISION_SHAPE_H
#define PROJECT_COLLISION_SHAPE_H

#include <memory>
#include <math/math_ifx.h>

class btCollisionShape;

namespace ifx {

class RigidBodyImpl;

enum class CollisionShapeType{
    StaticPlane, Box, Sphere
};

class CollisionShape {
public:

    CollisionShape();
    virtual ~CollisionShape() = default;

    const glm::vec3 &scale() { return scale_; }
    void scale(const glm::vec3 &scale) { scale_ = scale; }

    virtual void InitImpl(RigidBodyImpl *rigid_body_impl) = 0;
private:
    glm::vec3 scale_;
};

}

#endif //PROJECT_COLLISION_SHAPE_H
