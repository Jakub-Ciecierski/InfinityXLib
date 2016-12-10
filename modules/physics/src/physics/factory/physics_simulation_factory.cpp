#include "physics/factory/physics_simulation_factory.h"

#include <physics/physics_simulation.h>

namespace ifx {

PhysicsSimulationFactory::PhysicsSimulationFactory(){}

PhysicsSimulationFactory::~PhysicsSimulationFactory(){}

std::shared_ptr<PhysicsSimulation> PhysicsSimulationFactory::Create(){
    auto physics_simulation
            = std::shared_ptr<PhysicsSimulation>(new PhysicsSimulation());
    return physics_simulation;
}

}