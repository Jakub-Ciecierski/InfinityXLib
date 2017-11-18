#include "editor/views/soft_body_views/solver/soft_body_solver_view.h"

#include "editor/views/soft_body_views/soft_body_structers.h"
#include <editor/views/soft_body_views/solver/dynamic/soft_body_dynamic_solver_view.h>

#include <game/components/physics/soft_body_fem_component.h>
#include <game/components/render/render_component.h>
#include <game/scene_container.h>
#include <game/game_object.h>

#include <gui/imgui/imgui.h>

#include <graphics/model/model.h>
#include <graphics/model/mesh.h>
#include <graphics/shaders/buffers/vbo.h>
#include <graphics/shaders/data/shader_data.h>

#include <RTFEM/FEM/Solver/FEMSolvers/FEMStaticSolver.h>

#include <RTFEM/FEM/FEMModel.h>
#include <RTFEM/FEM/FEMGeometry.h>
#include <RTFEM/FEM/Vertex.h>

#include <common/unique_ptr.h>

#include <physics/physics_simulation.h>

namespace ifx {

SoftBodySolverView::SoftBodySolverView(
    std::shared_ptr<SceneContainer> scene_container,
    std::shared_ptr<PhysicsSimulation> physics_simulation) :
    solver_type_(rtfem::AnalysisSolverType::Dynamic),
    physics_simulation_(physics_simulation){
    dynamic_solver_view_
            = ifx::make_unique<SoftBodyDynamicSolverView>(scene_container,
                                                          physics_simulation);
}

void SoftBodySolverView::Render(SoftBodyEditorObjects& soft_body_objects,
                                SoftBodyRenderingEffects &rendering_effects){
    RenderSolverType();

    switch(soft_body_solvers_.selected){
        case soft_body_solvers_.dynamic_id:
            dynamic_solver_view_->Render(soft_body_objects,
                                         rendering_effects);
            break;
        case soft_body_solvers_.static_id:
            RenderStatic(soft_body_objects);
            break;
    }
}

void SoftBodySolverView::RenderSolverType(){
    ImGui::Text("Solver Type:");
    ImGui::SameLine();
    if (ImGui::Button(soft_body_solvers_.names[soft_body_solvers_.selected].c_str(),
                      ImVec2(80, 20))){
        ImGui::OpenPopup("SoftBodySolverView");
    }
    if (ImGui::BeginPopup("SoftBodySolverView")) {
        for (unsigned int i = 0; i < soft_body_solvers_.names.size(); i++){
            if (ImGui::Selectable(soft_body_solvers_.names[i].c_str())){
                soft_body_solvers_.selected = i;
            }
        }
        ImGui::EndPopup();
    }
}

void SoftBodySolverView::RenderStatic(SoftBodyEditorObjects& soft_body_objects){
    if(ImGui::Button("Solve")){
        auto soft_body_fem_component
                = soft_body_objects.soft_body_fem_component_builder->Build(
                physics_simulation_);
        auto fem_model = soft_body_fem_component->fem_model();
        rtfem::FEMStaticSolver<double> fem_solver(fem_model);
        auto fem_solver_output = fem_solver.Solve();

        auto* vbo = soft_body_objects
                .soft_body_fem_component_builder->fem_render()->
                models()[0]->getMesh(0)->vbo();

        auto* vertices = vbo->vertices();
        for(unsigned int i = 0; i < vertices->size(); i++){
            auto& vertex = (*vertices)[i];
            auto displacement_index_start = i * 3;
            auto displacement_x
                    = fem_solver_output.displacement[displacement_index_start];
            auto displacement_y
                    = fem_solver_output.displacement[displacement_index_start + 1];
            auto displacement_z
                    = fem_solver_output.displacement[displacement_index_start + 2];

            vertex.Position.x += displacement_x;
            vertex.Position.y += displacement_y;
            vertex.Position.z += displacement_z;

            auto &fem_vertex
                    = soft_body_objects.soft_body_fem_component_builder
                            ->GetFEMGeometry().vertices[i];
            const auto& coordinates = fem_vertex->coordinates();
            fem_vertex->coordinates(
                    coordinates + Eigen::Vector3<double>(
                            displacement_x, displacement_y, displacement_z)
            );
        }

        vbo->Update();
    }
}

}