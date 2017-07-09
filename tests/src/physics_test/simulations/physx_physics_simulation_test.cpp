#include "physics_test/simulations/physx_physics_simulation_test.h"

#include <physics/simulations/physx_physics_simulation.h>
#include <physics/factory/physx_physics_simulation_factory.h>

void PhysxPhysicsSimulationTest::SetUp() {
    ifx::PhysxPhysicsSimulationFactory factory;
    simulation_ = std::static_pointer_cast<ifx::PhysxPhysicsSimulation>(
            factory.Create());
}

void PhysxPhysicsSimulationTest::TearDown() {
}

TEST_F(PhysxPhysicsSimulationTest, Test1){
}