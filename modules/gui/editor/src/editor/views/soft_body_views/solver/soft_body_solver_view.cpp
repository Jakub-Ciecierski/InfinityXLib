#include "editor/views/soft_body_views/solver/soft_body_solver_view.h"

#include "editor/views/soft_body_views/soft_body_structers.h"

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
    std::shared_ptr<SceneContainer> scene_container) :
    solver_type_(rtfem::AnalysisSolverType::Dynamic),
    fem_dynamic_solver_(nullptr),
    scene_container_(scene_container){}

void SoftBodySolverView::Render(SoftBodyEditorObjects& soft_body_objects){
    if(ImGui::Button("Solve Dynamic")){
        RenderDynamic(soft_body_objects);
    }

    if(ImGui::Button("Solve")){
        auto soft_body_fem_component
            = soft_body_objects.soft_body_fem_component_builder->Build();
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

void SoftBodySolverView::RenderDynamic(
    SoftBodyEditorObjects& soft_body_objects){
    soft_body_fem_component_
        = soft_body_objects.soft_body_fem_component_builder->Build();
    auto game_object = scene_container_->CreateAndAddEmptyGameObject();
    game_object->Add(soft_body_fem_component_);
}


}