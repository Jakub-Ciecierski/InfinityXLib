#ifndef PROJECT_FRACTURE_RIGID_BODY_H
#define PROJECT_FRACTURE_RIGID_BODY_H

#include <physics/rigid_body.h>

class btFractureBody;

namespace ifx {

class BulletPhysicsSimulation;

class FractureRigidBody : public RigidBody {
public:

    FractureRigidBody(std::shared_ptr<CollisionShape> collision_shape,
                      float mass,
                      std::shared_ptr<BulletPhysicsSimulation> simulation);
    FractureRigidBody(std::shared_ptr<btFractureBody> fracture_body_bt);

    ~FractureRigidBody();

private:
    void Init();

    std::shared_ptr<BulletPhysicsSimulation> simulation_;
};
}

#endif //PROJECT_FRACTURE_RIGID_BODY_H
