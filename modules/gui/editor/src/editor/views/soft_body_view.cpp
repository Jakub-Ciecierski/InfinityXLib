#include "editor/views/soft_body_view.h"

#include <game/game_updater.h>
#include <game/game_object.h>
#include <game/scene_container.h>
#include <game/architecture/engine_architecture.h>
#include <game/game_component.h>
#include <game/components/render/render_component.h>
#include "game/resources/resource_context.h"

#include <physics/physics_simulation.h>

#include <gui/imgui/imgui.h>

#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/rendering/scene_renderer.h>
#include <graphics/rendering/rendering_effect.h>
#include <graphics/shaders/textures/texture.h>

#include <editor/views/soft_body_views/meshing_builder.h>
#include "editor/views/soft_body_views/soft_body_screen_view.h"
#include "editor/views/soft_body_views/soft_body_settings_view.h"
#include <editor/views/soft_body_views/soft_body_creator_view.h>
#include <editor/views/soft_body_views/soft_body_selector.h>

#include <common/unique_ptr.h>

namespace ifx {

SoftBodyView::SoftBodyView(std::unique_ptr<GameUpdater> game_updater,
                           const SoftBodyRenderingEffects &rendering_effects) :
    View("Soft Body"),
    game_updater_(std::move(game_updater)),
    rendering_effects_(rendering_effects),
    soft_body_objects_(SoftBodyObjects{nullptr, nullptr, nullptr}),
    first_render_(true) {
    screen_view_ = ifx::make_unique<SoftBodyScreenView>();
    settings_view_ = ifx::make_unique<SoftBodySettingsView>();
    creator_view_ = ifx::make_unique<SoftBodyCreatorView>(
        game_updater_->engine_architecture()->
            engine_contexts.resource_context->
            resource_manager());
    selector_ = ifx::make_unique<SoftBodySelector>(
        game_updater_->engine_architecture()->
            engine_systems.scene_container);
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
    settings_view_->Render(soft_body_objects_,
                           rendering_effects_);
    if (creator_view_->Render(settings_view_->rtfem_options(),
                              soft_body_objects_,
                              rendering_effects_)) {
        settings_view_->SetRenderObjectMode(RenderObjectMode::Output);
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