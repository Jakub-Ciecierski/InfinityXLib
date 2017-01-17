#ifndef PROJECT_BOXCOLLISIONSHAPE_H
#define PROJECT_BOXCOLLISIONSHAPE_H

#include <math/math_ifx.h>
#include <physics/collision/collision_shape.h>

namespace ifx {

class BoxCollisionShape : public CollisionShape{
public:

    BoxCollisionShape(const glm::vec3 dim);
    ~BoxCollisionShape();

private:
};
}

#endif //PROJECT_BOXCOLLISIONSHAPE_H
