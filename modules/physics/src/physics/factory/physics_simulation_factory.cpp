#include "physics/factory/physics_simulation_factory.h"

#include <physics/physics_simulation.h>
#include <physics/simulations/bullet_physics_simulation.h>

namespace ifx {

PhysicsSimulationFactory::PhysicsSimulationFactory(){}

PhysicsSimulationFactory::~PhysicsSimulationFactory(){}

std::shared_ptr<PhysicsSimulation> PhysicsSimulationFactory::Create(){
    auto physics_simulation
            = std::shared_ptr<PhysicsSimulation>(new BulletPhysicsSimulation());
    return physics_simulation;
}

}