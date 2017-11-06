#ifndef PROJECT_SPHERE_COLLISION_SHAPE_H
#define PROJECT_SPHERE_COLLISION_SHAPE_H

#include <physics/collision/collision_shape.h>

namespace ifx {

class SphereCollisionShape : public CollisionShape {
public:
    SphereCollisionShape(float radius);
    ~SphereCollisionShape() = default;

    float radius() const {return radius_;}

    virtual void InitImpl(RigidBodyImpl *rigid_body_impl) override;
private:
    float radius_;
};
}


#endif //PROJECT_SPHERE_COLLISION_SHAPE_H
