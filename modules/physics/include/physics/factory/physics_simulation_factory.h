#ifndef PROJECT_PHYSICS_SIMULATION_FACTORY_H
#define PROJECT_PHYSICS_SIMULATION_FACTORY_H

#include <memory>

namespace ifx {

class PhysicsSimulation;
class PhysicsContext;

class PhysicsSimulationFactory {
public:

    PhysicsSimulationFactory() = default;
    virtual ~PhysicsSimulationFactory() = default;

    virtual std::shared_ptr<PhysicsSimulation> Create(
        std::shared_ptr<PhysicsContext> physics_context) = 0;
private:
};
}

#endif //PROJECT_PHYSICS_SIMULATION_FACTORY_H
