#include "editor/views/physics_simulation_view.h"

#include <gui/imgui/imgui.h>

#include <physics/physics_simulation.h>

namespace ifx {

PhysicsSimulationView::PhysicsSimulationView(
    std::shared_ptr<PhysicsSimulation> physics_simulation) :
    View("Physics"),
    physics_simulation_(physics_simulation) {}

void PhysicsSimulationView::Render() {
    RenderBasicInfo();
    RenderGravity();
    RenderTimeStep();
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

    ImGui::PushItemWidth(150);
    ImGui::SliderFloat3("Gravity", raw, -20, 20);
    ImGui::PopItemWidth();
    
    gravity.x = raw[0];
    gravity.y = raw[1];
    gravity.z = raw[2];

    physics_simulation_->SetGravity(gravity);
}

void PhysicsSimulationView::RenderTimeStep(){
    float time_step_hz = 1.0f / physics_simulation_->fixed_time_delta();

    ImGui::PushItemWidth(75);

    if(ImGui::InputFloat("Time Step [Hz]", &time_step_hz)){
        float time_step_s = 1.0f / time_step_hz;
        physics_simulation_->fixed_time_delta(time_step_s);
    }

    ImGui::PopItemWidth();
}

}