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

#include <common/unique_ptr.h>

#include <RTFEM/FEM/Meshing/Tetrahedralization.h>

namespace ifx {

SoftBodyView::SoftBodyView(std::unique_ptr<GameUpdater> game_updater,
                           const SoftBodyRenderingEffects &rendering_effects) :
    View("Soft Body"),
    game_updater_(std::move(game_updater)),
    rendering_effects_(rendering_effects),
    soft_body_objects_(SoftBodyObjects{nullptr, nullptr, nullptr}),
    first_render_(true),
    soft_body_fem_(nullptr){
    screen_view_ = ifx::make_unique<SoftBodyScreenView>();
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
    boundarary_conditions_view_ = ifx::make_unique<SoftBodyBoundaryConditionsView>();
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
        for (unsigned int i = 0; i < soft_body_views.names.size(); i++)
            if (ImGui::Selectable(soft_body_views.names[i].c_str()))
                soft_body_views.selected = i;
        ImGui::EndPopup();
    }
    ImGui::Separator();

    bool mesh_created = false;

    switch(soft_body_views.selected){
        case soft_body_views.guide_id:
            soft_body_guide_view_->Render(soft_body_objects_);
            break;
        case soft_body_views.meshing_id:
            mesh_created = meshing_view_->Render(soft_body_objects_,
                                                 rendering_effects_);
            break;
        case soft_body_views.material_id:
            material_view_->Render(soft_body_objects_.soft_body_fem);
            break;
        case soft_body_views.boudary_conditions_id:
            break;
        case soft_body_views.load_id:
            break;
        case soft_body_views.rendering_id:
            rendering_view_->Render(soft_body_objects_,
                                    rendering_effects_);
            break;
        case soft_body_views.solver_id:
            break;
        default:
            break;

    }

    if(mesh_created){
        rendering_view_->SetRenderObjectMode(RenderObjectMode::Output);
    }
}

void SoftBodyView::RenderRightColumn() {
    if (first_render_)
        ImGui::SetColumnOffset(-1, 150);
    screen_view_->Render(game_updater_->engine_architecture()->
        engine_systems.renderer);
}

void SoftBodyView::OnSetSelectedGameObject(
    std::shared_ptr<GameObject> selected_game_object) {
    selector_->Select(selected_game_object,
                      rendering_effects_,
                      soft_body_objects_);
}

}