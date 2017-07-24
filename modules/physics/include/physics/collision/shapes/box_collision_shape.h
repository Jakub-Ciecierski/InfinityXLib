#ifndef PROJECT_BOXCOLLISIONSHAPE_H
#define PROJECT_BOXCOLLISIONSHAPE_H

#include <physics/collision/collision_shape.h>
#include <math/math_ifx.h>

namespace ifx {

class BoxCollisionShape : public CollisionShape{
public:

    BoxCollisionShape(const glm::vec3& dim);
    ~BoxCollisionShape();

    const glm::vec3& dimension() const {return dimension_;}

    virtual void InitImpl(RigidBodyImpl* rigid_body_impl) override;

private:
    glm::vec3 dimension_;
};
}

#endif //PROJECT_BOXCOLLISIONSHAPE_H
