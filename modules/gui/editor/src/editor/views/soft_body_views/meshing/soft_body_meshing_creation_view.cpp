#include "editor/views/soft_body_views/meshing/soft_body_meshing_creation_view.h"

#include <editor/views/soft_body_views/soft_body_structers.h>

#include <game/game_object.h>
#include <game/game_component.h>
#include <game/components/render/render_component.h>
#include <game/components/physics/soft_body_fem_component.h>
#include "game/components/physics/builder/meshing_builder.h"

#include <graphics/rendering/rendering_effect.h>

#include <gui/imgui/imgui.h>

#include <RTFEM/FEM/Vertex.h>
#include <RTFEM/FEM/FiniteElement.h>
#include <RTFEM/FEM/BoundaryConditionContainer.h>
#include <RTFEM/FEM/BoundaryCondition.h>

#include <iostream>

#include <GL/glew.h>

namespace ifx {

SoftBodyMeshingCreationView::SoftBodyMeshingCreationView(
    std::shared_ptr<ResourceManager> resource_manager) :
    resource_manager_(resource_manager) {}

bool SoftBodyMeshingCreationView::Render(
    const rtfem::TetrahedralizationOptions &rtfem_options,
    SoftBodyEditorObjects &soft_body_objects,
    SoftBodyRenderingEffects &rendering_effects) {
    bool return_value = false;
    if (ImGui::TreeNodeEx("Creation",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        if (ImGui::Button("Compute Mesh")) {
            return_value = BuildMesh(rtfem_options,
                                     soft_body_objects,
                                     rendering_effects);
        }
        if (DebugCreator(rtfem_options, soft_body_objects, rendering_effects)) {
            return_value = true;
        }
        ImGui::TreePop();
    }

    return return_value;
}

bool SoftBodyMeshingCreationView::BuildMesh(
    const rtfem::TetrahedralizationOptions &rtfem_options,
    SoftBodyEditorObjects &soft_body_objects,
    SoftBodyRenderingEffects &rendering_effects) {
    if (!soft_body_objects.current_game_object) {
        return false;
    }
    soft_body_objects.current_game_object->Remove(
            soft_body_objects.current_fem_render_component);
    rtfem::TriangleMeshIndexed<double> triangle_mesh;
    try {
        triangle_mesh = CreateTriangleMesh(soft_body_objects);
    } catch (const std::invalid_argument &) {
        return false;
    }

    soft_body_objects.soft_body_fem_component_builder->GetBoundaryConditions()
        = rtfem::BoundaryConditionContainer<double>();

    auto fem_geometry = CreateFEMGeometry(rtfem_options, triangle_mesh);
    soft_body_objects.soft_body_fem_component_builder->GetFEMGeometry()
        = fem_geometry;
    soft_body_objects.soft_body_fem_component_builder->fem_render(
        CreateRenderComponent(fem_geometry));

    RegisterRenderComponent(
        soft_body_objects.soft_body_fem_component_builder->fem_render(),
        soft_body_objects,
        rendering_effects);

    return true;
}

rtfem::TriangleMeshIndexed<double>
SoftBodyMeshingCreationView::CreateTriangleMesh(SoftBodyEditorObjects &soft_body_objects) {
    auto render_components
        = soft_body_objects.current_game_object->GetComponents(
            std::move(GameComponentType::RENDER));
    if (render_components.size() != MAX_RENDER_COMPONENTS) {
        throw std::invalid_argument("Render Component count incorrect");
    }

    return MeshingBuilder<double>().CreateTriangleMesh(
        std::dynamic_pointer_cast<RenderComponent>(render_components[0])
    );
}

rtfem::FEMGeometry<double>
SoftBodyMeshingCreationView::CreateFEMGeometry(
    const rtfem::TetrahedralizationOptions &rtfem_options,
    const rtfem::TriangleMeshIndexed<double> &triangle_mesh) {
    rtfem::Tetrahedralization<double> tetrahedralization;
    tetrahedralization.SetOptions(rtfem_options);
    return tetrahedralization.Compute(triangle_mesh);
}

std::shared_ptr<RenderComponent> SoftBodyMeshingCreationView::CreateRenderComponent(
    const rtfem::FEMGeometry<double> &fem_geometry) {
    return MeshingBuilder<double>().CreateRenderComponent(
        fem_geometry, resource_manager_);
}

void SoftBodyMeshingCreationView::RegisterRenderComponent(
    std::shared_ptr<RenderComponent> render_component,
    SoftBodyEditorObjects &soft_body_objects,
    SoftBodyRenderingEffects &rendering_effects) {
    rendering_effects.Register(render_component);
    soft_body_objects.UpdateFEMRenderComponent(render_component);
}

bool SoftBodyMeshingCreationView::DebugCreator(
    const rtfem::TetrahedralizationOptions &rtfem_options,
    SoftBodyEditorObjects &soft_body_objects,
    SoftBodyRenderingEffects &rendering_effects) {
    static float limit = 1;
    if (ImGui::SliderFloat("Tet%", &limit, 0, 1)) {
        if (!soft_body_objects.current_game_object) {
            return false;
        }
        soft_body_objects.current_game_object->Remove(
            soft_body_objects.soft_body_fem_component_builder->fem_render());

        rtfem::TriangleMeshIndexed<double> triangle_mesh;
        try {
            triangle_mesh = CreateTriangleMesh(soft_body_objects);
        } catch (const std::invalid_argument &) {
            return false;
        }

        auto fem_geometry = CreateFEMGeometry(rtfem_options, triangle_mesh);

        // <limit>
        std::vector<std::shared_ptr<rtfem::FiniteElement<double>>>
            finite_elements;
        std::sort(fem_geometry.finite_elements.begin(),
                  fem_geometry.finite_elements.end(),
                  [&fem_geometry](
                      std::shared_ptr<rtfem::FiniteElement<double>> a,
                      std::shared_ptr<rtfem::FiniteElement<double>> b) -> bool {
                      auto a_indices = a->vertices_indices();
                      auto b_indices = b->vertices_indices();
                      auto a_avg_x =
                          (fem_geometry.vertices[a_indices[0]]->x()
                              + fem_geometry.vertices[a_indices[1]]->x()
                              + fem_geometry.vertices[a_indices[2]]->x()
                              + fem_geometry.vertices[a_indices[3]]->x()) / 4.0;

                      auto b_avg_x =
                          (fem_geometry.vertices[b_indices[0]]->x()
                              + fem_geometry.vertices[b_indices[1]]->x()
                              + fem_geometry.vertices[b_indices[2]]->x()
                              + fem_geometry.vertices[b_indices[3]]->x()) / 4.0;

                      return a_avg_x < b_avg_x;
                  });

        unsigned int new_size
            = limit * fem_geometry.finite_elements.size();
        for (unsigned int i = 0; i < new_size; i++) {
            finite_elements.push_back(
                fem_geometry.finite_elements[i]);
        }
        fem_geometry.finite_elements = finite_elements;
        // </limit>

        soft_body_objects.soft_body_fem_component_builder->fem_render(
            CreateRenderComponent(fem_geometry));
        RegisterRenderComponent(
            soft_body_objects.soft_body_fem_component_builder->fem_render(),
            soft_body_objects,
            rendering_effects);
        soft_body_objects.soft_body_fem_component_builder->GetFEMGeometry()
            = fem_geometry;

        return true;
    }

    return false;

}


}