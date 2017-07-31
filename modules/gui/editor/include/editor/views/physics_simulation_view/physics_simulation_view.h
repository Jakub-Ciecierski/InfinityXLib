#ifndef PROJECT_PHYSICS_SIMULATION_VIEW_H
#define PROJECT_PHYSICS_SIMULATION_VIEW_H

#include <memory>

#include <editor/view.h>

namespace ifx {

class PhysicsSimulation;

class PhysicsSimulationView : public View {
public:
    PhysicsSimulationView(std::shared_ptr<PhysicsSimulation> physics_simulation);

    ~PhysicsSimulationView() = default;

    virtual void Render() override;

private:
    void RenderBasicInfo();
    void RenderGravity();
    void RenderImpulse();

    std::shared_ptr<PhysicsSimulation> physics_simulation_;
};
}

#endif //PROJECT_PHYSICS_SIMULATION_VIEW_H
