#include "game/components/physics/rigid_body_component.h"

namespace ifx{

RigidBodyComponent::RigidBodyComponent(
        std::shared_ptr<CollisionShape>  collision_shape,
        float mass) :
        GameComponent(GameComponentType::PHYSICS),
        RigidBody(collision_shape, mass) {}

RigidBodyComponent::RigidBodyComponent() :
        GameComponent(GameComponentType::PHYSICS),
        RigidBody(){}

RigidBodyComponent::~RigidBodyComponent(){}

}