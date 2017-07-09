#include "physics/simulations/physx_physics_simulation.h"

#include <physics/impl/rigid_body_impl.h>

namespace ifx {

PhysxPhysicsSimulation::PhysxPhysicsSimulation() {}

PhysxPhysicsSimulation::~PhysxPhysicsSimulation() {}

void PhysxPhysicsSimulation::Update(float time_delta) {

}

void PhysxPhysicsSimulation::SetGravity(const glm::vec3 &g) {

}

glm::vec3 PhysxPhysicsSimulation::GetGravity() {
    //return nullptr;
}

void PhysxPhysicsSimulation::AddImpulse() {

}

std::unique_ptr<RigidBodyImpl> PhysxPhysicsSimulation::CreateRigidBodyImpl() {
    return std::unique_ptr<RigidBodyImpl>();
}

}