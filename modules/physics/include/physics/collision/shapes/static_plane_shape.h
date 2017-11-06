#ifndef PROJECT_STATIC_PLANE_SHAPE_H
#define PROJECT_STATIC_PLANE_SHAPE_H

#include <physics/collision/collision_shape.h>
#include <math/math_ifx.h>

namespace ifx {

class StaticPlaneShape : public CollisionShape {
public:

    StaticPlaneShape(const glm::vec3 &normal, float plane_constant);
    ~StaticPlaneShape() = default;

    const glm::vec3 &normal() const { return normal_; }
    float plane_constant() const { return plane_constant_; }

    virtual void InitImpl(RigidBodyImpl *rigid_body_impl) override;

private:
    glm::vec3 normal_;
    float plane_constant_;
};
}

#endif //PROJECT_STATIC_PLANE_SHAPE_H
