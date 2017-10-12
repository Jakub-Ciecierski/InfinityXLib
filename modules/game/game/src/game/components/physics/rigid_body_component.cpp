#include "game/components/physics/rigid_body_component.h"

#include <physics/physics_simulation.h>
#include <physics/impl/rigid_body_impl.h>

namespace ifx {

RigidBodyComponent::RigidBodyComponent(
    std::shared_ptr<PhysicsSimulation> physics_simulation,
    const RigidBodyParams &&params) :
    GameComponent(GameComponentType::PHYSICS),
    RigidBody(std::move(physics_simulation->CreateRigidBodyImpl()),
              std::move(params)) {

}

}