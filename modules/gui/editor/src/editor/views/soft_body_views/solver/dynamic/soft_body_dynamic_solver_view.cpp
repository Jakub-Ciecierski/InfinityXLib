#include "editor/views/soft_body_views/solver/dynamic/soft_body_dynamic_solver_view.h"

#include "editor/views/soft_body_views/soft_body_structers.h"

#include <game/scene_container.h>
#include <game/game_object.h>
#include <game/components/physics/soft_body_fem_component.h>

#include <gui/imgui/imgui.h>

#include <physics/physics_simulation.h>
#include <common/updatable.h>

namespace ifx {

SoftBodyDynamicSolverView::SoftBodyDynamicSolverView(
        std::shared_ptr<SceneContainer> scene_container,
        std::shared_ptr<PhysicsSimulation> physics_simulation) :
        scene_container_(scene_container),
        physics_simulation_(physics_simulation),
        soft_body_fem_component_(nullptr),
        soft_body_fem_game_object_(nullptr){
    soft_body_fem_game_object_
            = scene_container_->CreateAndAddEmptyGameObject();
    Pause();
}

void SoftBodyDynamicSolverView::Render(
        SoftBodyEditorObjects& soft_body_objects,
        SoftBodyRenderingEffects &rendering_effects){
    HandleTimeRestrictions();

    ImGui::PushItemWidth(60);

    RenderBuild(soft_body_objects, rendering_effects);
    ImGui::SameLine();
    RenderPlayPauseSolver();
    ImGui::SameLine();
    RenderStepSolver();

    ImGui::PopItemWidth();

    RenderSolverSettings();
    RenderSimulationInformation();
}

void SoftBodyDynamicSolverView::HandleTimeRestrictions(){
    if(time_restriction_.do_time_restriction){
        const auto& update_timer = physics_simulation_->update_timer();
        if(update_timer.total_time >= time_restriction_.time_seconds){
            Pause();
        }
    }
}

void SoftBodyDynamicSolverView::RenderBuild(
        SoftBodyEditorObjects& soft_body_objects,
        SoftBodyRenderingEffects &rendering_effects){
    if(ImGui::Button("Build")){
        if(soft_body_fem_component_){
            soft_body_fem_game_object_->Remove(soft_body_fem_component_);
        }
        soft_body_fem_component_
                = soft_body_objects.soft_body_fem_component_builder->Build(
            physics_simulation_);

        rendering_effects.Register(
                soft_body_fem_component_->render_component());
        soft_body_objects.UpdateFEMRenderComponent(
                soft_body_fem_component_->render_component());

        soft_body_fem_game_object_->Add(soft_body_fem_component_);

        physics_simulation_->ResetTimers();
        Pause();
    }
}

void SoftBodyDynamicSolverView::RenderPlayPauseSolver(){
    std::string button_name = "Play";
    auto is_running = physics_simulation_->is_running();
    if(is_running){
        button_name = "Pause";
    }
    if(ImGui::Button(button_name.c_str())){
        physics_simulation_->is_running(!is_running);
    }
}

void SoftBodyDynamicSolverView::RenderStepSolver(){
    if(ImGui::Button("Step")){
        Play();
        StepSolver();
        Pause();
    }
}

void SoftBodyDynamicSolverView::RenderSolverSettings(){
    RenderSetTimeStep();
    RenderSetTimeRestrictions();
}

void SoftBodyDynamicSolverView::RenderSetTimeStep(){
    if (ImGui::TreeNodeEx("Time steps [Hz]", ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderSetTimeStepPhysics();
        RenderSetTimeStepRenderingSynchronization();
        ImGui::TreePop();
    }
}

void SoftBodyDynamicSolverView::RenderSetTimeRestrictions(){
    if (ImGui::TreeNodeEx("Time Restrictions",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Checkbox(" ", &time_restriction_.do_time_restriction);
        if(time_restriction_.do_time_restriction){
            ImGui::PushItemWidth(65);
            ImGui::SameLine();
            ImGui::InputFloat("[s]", &time_restriction_.time_seconds);
            ImGui::PopItemWidth();
        }
        ImGui::TreePop();
    }
}

void SoftBodyDynamicSolverView::RenderSetTimeStepPhysics(){
    RenderUpdateSettings(physics_simulation_, "Physics");
}

void SoftBodyDynamicSolverView::RenderSetTimeStepRenderingSynchronization(){
    RenderUpdateSettings(scene_container_, "Synchronization");
}

void SoftBodyDynamicSolverView::RenderUpdateSettings(
        std::shared_ptr<Updatable> updatable,
        std::string name) {
    const float min = 5;
    float time_step_hz = 1.0f / updatable->fixed_time_delta();

    ImGui::PushItemWidth(65);

    if (ImGui::InputFloat(name.c_str(), &time_step_hz)) {
        if(time_step_hz < min){
            time_step_hz = min;
        }
        float time_step_s = 1.0f / time_step_hz;

        updatable->fixed_time_delta(time_step_s);
    }

    ImGui::PopItemWidth();
}

void SoftBodyDynamicSolverView::RenderSimulationInformation(){
    if (ImGui::TreeNodeEx("Info", ImGuiTreeNodeFlags_DefaultOpen)) {
        const auto& update_timer = physics_simulation_->update_timer();

        ImGui::Text("Time: %f [s]", update_timer.total_time);
        ImGui::Text("Iteration: %lu", update_timer.iterations);

        ImGui::TreePop();
    }
}

void SoftBodyDynamicSolverView::Play(){
    physics_simulation_->Play();
}

void SoftBodyDynamicSolverView::Pause(){
    physics_simulation_->Pause();
}

void SoftBodyDynamicSolverView::StepSolver(){
    physics_simulation_->Update(0);
}

}