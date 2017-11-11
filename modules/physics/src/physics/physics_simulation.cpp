#include "physics/physics_simulation.h"

#include <physics/soft_body/simulation/soft_body_fem_simulation.h>

#include <common/unique_ptr.h>

namespace ifx {

PhysicsSimulation::PhysicsSimulation(
    std::shared_ptr<PhysicsContext> physics_context) :
    physics_context_(physics_context),
    soft_body_fem_simulation_(
        std::move(ifx::make_unique<SoftBodyFEMSimulation<double>>())){}

void PhysicsSimulation::Add(std::shared_ptr<RigidBody> rigid_body) {
    rigid_bodies_.push_back(rigid_body);
}

bool PhysicsSimulation::Remove(std::shared_ptr<RigidBody> rigid_body) {
    for (unsigned int i = 0; i < rigid_bodies_.size(); i++) {
        if (rigid_bodies_[i] == rigid_body) {
            rigid_bodies_.erase(rigid_bodies_.begin() + i);
            return true;
        }
    }
    return false;
}

void PhysicsSimulation::UpdateFixedContent() {
    soft_body_fem_simulation_->Update(fixed_time_delta());
}

}