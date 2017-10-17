#include "editor/views/soft_body_view.h"

#include <game/game_updater.h>
#include <game/game_object.h>
#include <game/scene_container.h>
#include <game/architecture/engine_architecture.h>
#include <game/game_component.h>
#include <game/components/render/render_component.h>
#include "game/resources/resource_context.h"
#include <game/components/physics/soft_body_fem_component.h>

#include <physics/physics_simulation.h>

#include <gui/imgui/imgui.h>
#include <gui/imgui/imgui_internal.h>

#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/rendering/scene_renderer.h>
#include <graphics/rendering/rendering_effect.h>
#include <graphics/shaders/textures/texture.h>

#include <editor/views/soft_body_views/meshing/meshing_builder.h>
#include "editor/views/soft_body_views/soft_body_screen_view.h"
#include <editor/views/soft_body_views/soft_body_selector.h>
#include <editor/views/soft_body_views/solver/soft_body_solver_view.h>
#include <editor/views/soft_body_views/boundary_conditions/soft_body_boundary_conditions_view.h>
#include <editor/views/soft_body_views/meshing/soft_body_meshing_view.h>
#include <editor/views/soft_body_views/rendering/soft_body_rendering_view.h>
#include <editor/views/soft_body_views/material/soft_body_material_view.h>
#include <editor/views/soft_body_views/load/soft_body_load_view.h>
#include "editor/views/soft_body_views/meshing/soft_body_meshing_settings_view.h"
#include "editor/views/soft_body_views/meshing/soft_body_meshing_creation_view.h"
#include "editor/views/soft_body_views/meshing/soft_body_meshing_info_view.h"
#include <editor/views/soft_body_views/guide/soft_body_guide_view.h>
#include <editor/views/soft_body_views/picking/ray_casting.h>
#include <editor/views/soft_body_views/picking/box_casting.h>
#include "editor/views/soft_body_views/picking/soft_body_picker.h"
#include "editor/views/soft_body_views/picking/soft_body_node_selection.h"

#include <common/unique_ptr.h>

#include <RTFEM/FEM/Meshing/Tetrahedralization.h>

namespace ifx {

SoftBodyView::SoftBodyView(std::unique_ptr<GameUpdater> game_updater,
                           const SoftBodyRenderingEffects &rendering_effects,
                           std::shared_ptr<SoftBodyPicker> soft_body_picker) :
    View("Soft Body"),
    game_updater_(std::move(game_updater)),
    rendering_effects_(rendering_effects),
    soft_body_objects_(SoftBodyEditorObjects{nullptr, nullptr}),
    first_render_(true),
    soft_body_fem_(nullptr){
    screen_view_ = ifx::make_unique<SoftBodyScreenView>(soft_body_picker);
    selector_ = ifx::make_unique<SoftBodySelector>(
        game_updater_->engine_architecture()->
            engine_systems.scene_container);

    soft_body_guide_view_ = ifx::make_unique<SoftBodyGuideView>();
    meshing_view_ = ifx::make_unique<SoftBodyMeshingView>(
        game_updater_->engine_architecture()->
            engine_contexts.resource_context->
            resource_manager());
    rendering_view_ = ifx::make_unique<SoftBodyRenderingView>();
    material_view_ = ifx::make_unique<SoftBodyMaterialView>();
    boundarary_conditions_view_
        = ifx::make_unique<SoftBodyBoundaryConditionsView>(
        soft_body_picker);
    load_view_ = ifx::make_unique<SoftBodyLoadView>();
    solver_view_ = ifx::make_unique<SoftBodySolverView>();
}

bool SoftBodyView::Terminate() {
    game_updater_->engine_architecture()->engine_systems
        .physics_simulation->Terminate();
    return true;
}

void SoftBodyView::Render() {
    game_updater_->Update(1.0f / 60.0f);

    ImGui::Columns(2, "Soft");
    RenderLeftColumn();

    ImGui::NextColumn();
    RenderRightColumn();

    ImGui::Columns(1);

    first_render_ = false;
}

void SoftBodyView::RenderLeftColumn() {
    if (ImGui::Button(soft_body_views.names[soft_body_views.selected].c_str(),
                      ImVec2(150, 20))){
        ImGui::OpenPopup("select");
    }

    if (ImGui::BeginPopup("select")) {
        for (unsigned int i = 0; i < soft_body_views.names.size(); i++){
            if (ImGui::Selectable(soft_body_views.names[i].c_str())){
                soft_body_views.selected = i;
            }
            if(i == 0){
                ImGui::Separator();
            }
        }
        ImGui::EndPopup();
    }
    ImGui::Separator();

    bool mesh_created = false;

    auto* builder = soft_body_objects_.soft_body_fem_component_builder.get();
    switch(soft_body_views.selected){
        case soft_body_views.guide_id:
            soft_body_guide_view_->Render(soft_body_objects_);
            break;
        case soft_body_views.meshing_id:
            mesh_created = meshing_view_->Render(soft_body_objects_,
                                                 rendering_effects_);
            break;
        case soft_body_views.material_id:
            if(RenderError(builder)){
                material_view_->Render(builder->GetMaterial());
            }

            break;
        case soft_body_views.boudary_conditions_id:
            if(RenderError(builder)){
                boundarary_conditions_view_->Render(
                    builder->GetBoundaryConditions(),
                    builder->GetFEMGeometry()
                );
            }else{
                boundarary_conditions_view_->ResetSelectedBoundaryCondition();
            }

            break;
        case soft_body_views.load_id:
            if(RenderError(builder)){
                load_view_->Render(builder->GetBodyForce());
            }
            break;
        case soft_body_views.rendering_id:
            if(RenderError(builder)){
                rendering_view_->Render(builder->triangle_mesh_render(),
                                        builder->fem_render(),
                                        rendering_effects_);
            }

            break;
        case soft_body_views.solver_id:
            if(RenderError(builder)){
                solver_view_->Render(soft_body_objects_);
            }
            break;
        default:
            break;

    }

    if(mesh_created){
        rendering_view_->SetRenderObjectMode(RenderObjectMode::Output);
        if(builder){
            rendering_view_->UpdateRenderObjectMode(
                builder->triangle_mesh_render(),
                builder->fem_render());
        }

    }
}

void SoftBodyView::RenderRightColumn() {
    if (first_render_)
        ImGui::SetColumnOffset(-1, 150);

    std::shared_ptr<RenderComponent> fem_render_component = nullptr;
    if(soft_body_objects_.soft_body_fem_component_builder){
        fem_render_component
            = soft_body_objects_.soft_body_fem_component_builder->fem_render();
    }

    screen_view_->Render(
        game_updater_->engine_architecture()->engine_systems.renderer,
        fem_render_component);
}

void SoftBodyView::OnSetSelectedGameObject(
    std::shared_ptr<GameObject> selected_game_object) {
    selector_->Select(selected_game_object,
                      rendering_effects_,
                      soft_body_objects_);
}

bool SoftBodyView::RenderError(
    SoftBodyFEMComponentBuilder<double>* soft_body_fem_component_builder){
    bool return_value = true;
    if(!soft_body_fem_component_builder){
        ImGui::BeginChild(ImGui::GetID((void *) (intptr_t) 1),
                          ImVec2(-1, -1), false);

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255, 0, 0, 255));
        ImGui::Bullet();
        ImGui::SameLine();
        ImGui::TextWrapped("No Game Object Selected");
        ImGui::PopStyleColor();

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 255, 0, 255));
        ImGui::Bullet();
        ImGui::SameLine();
        ImGui::TextWrapped("To create new SoftBody: select GameObject with "
                               "single RenderComponent");
        ImGui::PopStyleColor();

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 255, 0, 255));
        ImGui::Bullet();
        ImGui::SameLine();
        ImGui::TextWrapped("To edit existing SoftBody: select GameObject with "
                               "SoftBody Component");
        ImGui::PopStyleColor();
        
        return_value = false;

        ImGui::EndChild();
    }
    return return_value;
}

}