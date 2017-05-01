#ifndef PROJECT_RIGIDBODYCOMPONENT_H
#define PROJECT_RIGIDBODYCOMPONENT_H

#include <game/game_component.h>
#include <physics/rigid_body.h>

namespace ifx {

class RigidBodyComponent : public GameComponent, public RigidBody {
public:

    RigidBodyComponent(std::shared_ptr<CollisionShape> collision_shape,
                       float mass);
    RigidBodyComponent();

    ~RigidBodyComponent();

private:
};
}

#endif //PROJECT_RIGIDBODYCOMPONENT_H
