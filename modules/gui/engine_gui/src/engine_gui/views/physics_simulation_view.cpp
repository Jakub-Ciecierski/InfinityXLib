#include "engine_gui/views/physics_simulation_view.h"

#include <physics/physics_simulation.h>
#include <gui/imgui/imgui.h>

namespace ifx{

PhysicsSimulationView::PhysicsSimulationView(
                std::shared_ptr<PhysicsSimulation> physics_simulation) :
        physics_simulation_(physics_simulation){}
PhysicsSimulationView::~PhysicsSimulationView(){}

void PhysicsSimulationView::Render(){
    ImGui::Begin("Physics");

    if(ImGui::TreeNode("Simulation")){
        RenderBasicInfo();
        ImGui::TreePop();
    }

    RenderImpulse();

    ImGui::End();

}

void PhysicsSimulationView::RenderBasicInfo(){
    bool is_running = physics_simulation_->is_running();
    std::string button_display = is_running ? "Pause" : "Play";

    if(ImGui::Button(button_display.c_str())){
        physics_simulation_->is_running(!is_running);
    }
}

void PhysicsSimulationView::RenderImpulse(){
    if(ImGui::Button("Impulse")){
        physics_simulation_->AddImpulse();
    }
}

}