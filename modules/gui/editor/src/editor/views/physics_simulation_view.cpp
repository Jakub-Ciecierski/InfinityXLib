#include "editor/views/physics_simulation_view.h"

#include <gui/imgui/imgui.h>

#include <physics/physics_simulation.h>

namespace ifx {

PhysicsSimulationView::PhysicsSimulationView(
    std::shared_ptr<PhysicsSimulation> physics_simulation) :
    View("Physics"),
    physics_simulation_(physics_simulation) {}

void PhysicsSimulationView::Render() {
    if (ImGui::TreeNode("Simulation")) {
        RenderBasicInfo();
        ImGui::TreePop();
    }
    RenderGravity();
    RenderImpulse();
}

void PhysicsSimulationView::RenderBasicInfo() {
    bool is_running = physics_simulation_->is_running();
    std::string button_display = is_running ? "Pause" : "Play";

    if (ImGui::Button(button_display.c_str())) {
        physics_simulation_->is_running(!is_running);
    }
}

void PhysicsSimulationView::RenderGravity() {
    static float raw[3];
    auto gravity = physics_simulation_->GetGravity();

    raw[0] = gravity.x;
    raw[1] = gravity.y;
    raw[2] = gravity.z;

    ImGui::SliderFloat3("Gravity", raw, -20, 20);
    gravity.x = raw[0];
    gravity.y = raw[1];
    gravity.z = raw[2];

    physics_simulation_->SetGravity(gravity);
}

void PhysicsSimulationView::RenderImpulse() {
    if (ImGui::Button("Impulse")) {
        physics_simulation_->AddImpulse();
    }
}

}