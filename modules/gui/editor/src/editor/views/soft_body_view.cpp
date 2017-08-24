#include "editor/views/soft_body_view.h"

#include <game/game_updater.h>
#include <game/architecture/engine_architecture.h>

#include <physics/physics_simulation.h>

#include <gui/imgui/imgui.h>

#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/shaders/textures/texture.h>

namespace ifx{

SoftBodyView::SoftBodyView(std::unique_ptr<GameUpdater> game_updater) :
        View("Soft Body"),
        game_updater_(std::move(game_updater)){}

bool SoftBodyView::Terminate() {
    game_updater_->engine_architecture()->engine_systems
            .physics_simulation->Terminate();
    return true;
}

void SoftBodyView::Render(){
    game_updater_->Update(1.0f/60.0f);

    auto fbo_renderer = std::dynamic_pointer_cast<FBORenderer>(
            game_updater_->engine_architecture()->engine_systems.renderer);
    if(fbo_renderer){

    }
    const auto& texture = fbo_renderer->GetSceneTexture();
    auto tex_id = texture.id();
    ImTextureID im_tex_id = (void*)(tex_id);

    ImGui::Image(im_tex_id, ImVec2(-1, -1));
}

}
