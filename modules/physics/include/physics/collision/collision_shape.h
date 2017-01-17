#ifndef PROJECT_COLLISION_SHAPE_H
#define PROJECT_COLLISION_SHAPE_H

#include <memory>

class btCollisionShape;

namespace ifx {

class CollisionShape {
public:

    CollisionShape();
    virtual ~CollisionShape();

    std::shared_ptr<btCollisionShape> collision_shape_bt(){
        return collision_shape_bt_;}
protected:
    std::shared_ptr<btCollisionShape> collision_shape_bt_;

};
}

#endif //PROJECT_COLLISION_SHAPE_H
