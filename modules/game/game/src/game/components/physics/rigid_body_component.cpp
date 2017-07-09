#include "game/components/physics/rigid_body_component.h"

#include <physics/physics_simulation.h>
#include <physics/impl/rigid_body_impl.h>

namespace ifx{
/*
RigidBodyComponent::RigidBodyComponent(
        std::shared_ptr<CollisionShape>  collision_shape,
        float mass) :
        GameComponent(GameComponentType::PHYSICS),
        RigidBody(collision_shape, mass) {}

RigidBodyComponent::RigidBodyComponent() :
        GameComponent(GameComponentType::PHYSICS),
        RigidBody(){}
*/

RigidBodyComponent::RigidBodyComponent(
        std::shared_ptr<PhysicsSimulation> physics_simulation,
        const RigidBodyParams &&params) :
        GameComponent(GameComponentType::PHYSICS),
        RigidBody(std::move(physics_simulation->CreateRigidBodyImpl()),
                  std::move(params)) {

}

RigidBodyComponent::~RigidBodyComponent(){}

}