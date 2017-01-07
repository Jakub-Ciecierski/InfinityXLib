#ifndef PROJECT_PHYSICSSIMULATIONFACTORY_H
#define PROJECT_PHYSICSSIMULATIONFACTORY_H

#include <memory>

namespace ifx {

class PhysicsSimulation;

class PhysicsSimulationFactory {
public:

    PhysicsSimulationFactory();
    ~PhysicsSimulationFactory();

    virtual std::shared_ptr<PhysicsSimulation> Create();

private:
};
}

#endif //PROJECT_PHYSICSSIMULATIONFACTORY_H
