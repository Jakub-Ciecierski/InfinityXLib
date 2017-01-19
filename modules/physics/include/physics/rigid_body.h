#ifndef PROJECT_RIGID_BODY_H
#define PROJECT_RIGID_BODY_H

#include <object/game_component.h>

class btRigidBody;
class btMotionState;

namespace ifx {

class CollisionShape;

class RigidBody : public GameComponent {
public:

    RigidBody(std::shared_ptr<CollisionShape> collision_shape, float mass);
    RigidBody();
    virtual ~RigidBody();

    std::shared_ptr<btRigidBody> rigid_body_bt(){return rigid_body_bt_;}

protected:

    std::shared_ptr<btRigidBody> rigid_body_bt_;
    std::shared_ptr<btMotionState> motion_state_bt_;

    std::shared_ptr<CollisionShape> collision_shape_;

    float mass_;
private:
    void Init();
};

}

#endif //PROJECT_RIGID_BODY_H
