#ifndef PROJECT_RIGID_BODY_H
#define PROJECT_RIGID_BODY_H

#include <math/transform.h>

class btRigidBody;
class btMotionState;

namespace ifx {

class CollisionShape;

class RigidBody : public Transformable {
public:

    RigidBody(std::shared_ptr<CollisionShape> collision_shape, float mass);
    RigidBody();
    virtual ~RigidBody();

    std::shared_ptr<btRigidBody> rigid_body_bt(){return rigid_body_bt_;}

    virtual void Update(float time_delta = 0) override;
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
