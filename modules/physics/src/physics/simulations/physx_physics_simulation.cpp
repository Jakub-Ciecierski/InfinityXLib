#include "physics/simulations/physx_physics_simulation.h"

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

std::shared_ptr<RigidBodyTMP>
PhysxPhysicsSimulation::CreatAndAdd(const RigidBodyParams &&params) {
    return nullptr;
}

}