#include "editor/views/soft_body_views/solver/dynamic/soft_body_dynamic_solver_view.h"

#include "editor/views/soft_body_views/soft_body_structers.h"

#include <game/scene_container.h>
#include <game/game_object.h>
#include <game/components/physics/soft_body_fem_component.h>

#include <gui/imgui/imgui.h>

#include <physics/physics_simulation.h>
#include <physics/soft_body/simulation/soft_body_fem_simulation.h>

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
    RenderComputationTimers();
}

void SoftBodyDynamicSolverView::HandleTimeRestrictions(){
    if(time_restriction_.do_time_restriction){
        const auto& update_timer = physics_simulation_->synchronization_timer();
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
    RenderSolverType();
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

void SoftBodyDynamicSolverView::RenderSolverType(){
    if (ImGui::TreeNodeEx("Type", ImGuiTreeNodeFlags_DefaultOpen)) {
        auto& soft_body_simulation =
                physics_simulation_->soft_body_fem_simulation();
        auto fem_solver_type = soft_body_simulation.GetFEMSolverType();

        bool use_gpu = fem_solver_type == rtfem::FEMSolverType::GPU;
        ImGui::Checkbox("GPU", &use_gpu);

        if(use_gpu){
            soft_body_simulation.SetFEMSolverType(
                    rtfem::FEMSolverType::GPU);
        }else{
            soft_body_simulation.SetFEMSolverType(
                    rtfem::FEMSolverType::CPU);
        }
        
        //
        ImGui::Text("Linear Solver:");
        ImGui::SameLine();
        if (ImGui::Button(linear_solvers_.names[linear_solvers_.selected].c_str(),
                          ImVec2(80, 17))){
            ImGui::OpenPopup("SoftBodyDynamicSolverView");
        }
        if (ImGui::BeginPopup("SoftBodyDynamicSolverView")) {
            for (unsigned int i = 0; i < linear_solvers_.names.size(); i++){
                if (ImGui::Selectable(linear_solvers_.names[i].c_str())){
                    linear_solvers_.selected = i;
                }
            }
            ImGui::EndPopup();
        }
        switch(linear_solvers_.selected){
            case linear_solvers_.cg_id: {
                physics_simulation_->soft_body_fem_simulation().
                        SetLinearSystemSolverType
                        (rtfem::LinearSystemSolverType::CG);
                break;
            }
            case linear_solvers_.cg_precond_id: {
                physics_simulation_->soft_body_fem_simulation().
                        SetLinearSystemSolverType
                        (rtfem::LinearSystemSolverType::CG_PreCond);
                break;
            }
            case linear_solvers_.lu_id: {
                physics_simulation_->soft_body_fem_simulation().
                        SetLinearSystemSolverType
                        (rtfem::LinearSystemSolverType::LU);
                break;
            }
        }

        //

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
        const auto& update_timer = physics_simulation_->synchronization_timer();

        ImGui::Text("Time: %f [s]", update_timer.total_time);
        ImGui::Text("Iteration: %lu", update_timer.iterations);

        ImGui::TreePop();
    }


}

void SoftBodyDynamicSolverView::RenderComputationTimers(){
    if(!soft_body_fem_component_){
        return;
    }
    if(!soft_body_fem_component_->last_fem_solver_output()){
        return;
    }

    if (ImGui::TreeNodeEx("Timers", ImGuiTreeNodeFlags_DefaultOpen)) {
        const auto& timer = soft_body_fem_component_->last_fem_solver_output()
                ->timer;
        auto total_time = timer.TotalTime();
        ImGui::Text("%.2f [ms]: Total Time", total_time);

        RenderComputationTimer("Force Reassemble",
                               total_time,
                               timer.reassemble_forces_time);
        RenderComputationTimer("RHS Solve",
                               total_time,
                               timer.rhs_solve_time);
        RenderComputationTimer("BC Solve",
                               total_time,
                               timer.boundary_conditions_solve_time);
        RenderComputationTimer("CUDA Solve",
                               total_time,
                               timer.cuda_solve_time);
        RenderComputationTimer("Integration Solve",
                               total_time,
                               timer.integration_solve_time);
        RenderComputationTimer("Reset Force",
                               total_time,
                               timer.reset_force_time);

        ImGui::TreePop();
    }
}

void SoftBodyDynamicSolverView::RenderComputationTimer(
        const std::string& name,
        double total_time,
        double time){
    std::string text = "%.2f: " + name;
    ImVec2 progress_bar_size{75, 20};
    ImGui::ProgressBar(time / total_time, progress_bar_size);
    ImGui::SameLine();
    ImGui::Text(text.c_str(),
                time,
                time / total_time);
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