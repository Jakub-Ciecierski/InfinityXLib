#include "editor/views/soft_body_view.h"

#include <game/game_updater.h>
#include <game/game_object.h>
#include <game/scene_container.h>
#include <game/architecture/engine_architecture.h>
#include <game/game_component.h>
#include <game/components/render/render_component.h>

#include <physics/physics_simulation.h>

#include <gui/imgui/imgui.h>

#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/shaders/textures/texture.h>

namespace ifx{

SoftBodyView::SoftBodyView(std::unique_ptr<GameUpdater> game_updater) :
        View("Soft Body"),
        game_updater_(std::move(game_updater)),
        current_game_object_(nullptr){}

bool SoftBodyView::Terminate() {
    game_updater_->engine_architecture()->engine_systems
            .physics_simulation->Terminate();
    return true;
}

void SoftBodyView::Render(){
    game_updater_->Update(1.0f/60.0f);

    auto fbo_renderer = std::dynamic_pointer_cast<FBORenderer>(
            game_updater_->engine_architecture()->engine_systems.renderer);
    if(!fbo_renderer)
        return;

    const auto& texture = fbo_renderer->GetSceneTexture();
    auto tex_id = texture.id();
    ImTextureID im_tex_id = (ImTextureID)(tex_id);
    ImGui::Image(im_tex_id, ImVec2(550, 550));
}

void SoftBodyView::SetGameObject(
        std::shared_ptr<GameObject> selected_game_object){
    auto scene = game_updater_->engine_architecture()->
            engine_systems.scene_container;
    if(current_game_object_){
        scene->Remove(current_game_object_);
    }
    current_game_object_ = scene->CreateAndAddEmptyGameObject();
    auto render_components = selected_game_object->GetComponents(
            std::move(GameComponentType::RENDER));

    for(auto& render_component : render_components){
        auto new_render_component = std::make_shared<RenderComponent>(
                std::dynamic_pointer_cast<RenderComponent>(
                        render_component)->models());
        current_game_object_->Add(new_render_component);
    }

}

}
