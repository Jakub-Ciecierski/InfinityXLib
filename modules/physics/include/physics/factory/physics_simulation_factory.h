#ifndef PROJECT_PHYSICS_SIMULATION_FACTORY_H
#define PROJECT_PHYSICS_SIMULATION_FACTORY_H

#include <memory>

namespace ifx {

class PhysicsSimulation;

class PhysicsSimulationFactory {
public:

    PhysicsSimulationFactory();

    ~PhysicsSimulationFactory();

    virtual std::shared_ptr<PhysicsSimulation> Create() = 0;

private:
};
}


#endif //PROJECT_PHYSICS_SIMULATION_FACTORY_H
