#ifndef PROJECT_PHYSICS_SIMULATION_VIEW_H
#define PROJECT_PHYSICS_SIMULATION_VIEW_H

#include <engine_gui/view.h>

#include <memory>

namespace ifx {

class PhysicsSimulation;

class PhysicsSimulationView : public View{
public:

    PhysicsSimulationView(std::shared_ptr<PhysicsSimulation> physics_simulation);
    ~PhysicsSimulationView();

    virtual void Render() override;
private:

    std::shared_ptr<PhysicsSimulation> physics_simulation_;
};
}

#endif //PROJECT_PHYSICS_SIMULATION_VIEW_H
