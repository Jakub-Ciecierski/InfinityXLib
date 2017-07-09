#ifndef PROJECT_COLLISION_SHAPE_H
#define PROJECT_COLLISION_SHAPE_H

#include <memory>

class btCollisionShape;

namespace ifx {

class RigidBodyImpl;

class CollisionShape {
public:

    CollisionShape();
    virtual ~CollisionShape();

    virtual void InitImpl(RigidBodyImpl* rigid_body_impl) = 0;
};

}

#endif //PROJECT_COLLISION_SHAPE_H
