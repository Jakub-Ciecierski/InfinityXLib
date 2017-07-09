#ifndef PROJECT_PHYSX_PHYSICS_SIMULATION_FACTORY_H
#define PROJECT_PHYSX_PHYSICS_SIMULATION_FACTORY_H

#include <physics/factory/physics_simulation_factory.h>

namespace ifx {

class PhysicsSimulation;

class PhysxPhysicsSimulationFactory : public PhysicsSimulationFactory {
public:

    PhysxPhysicsSimulationFactory();

    ~PhysxPhysicsSimulationFactory();

    std::shared_ptr<PhysicsSimulation> Create() override;

private:
};
}


#endif //PROJECT_PHYSX_PHYSICS_SIMULATION_FACTORY_H
