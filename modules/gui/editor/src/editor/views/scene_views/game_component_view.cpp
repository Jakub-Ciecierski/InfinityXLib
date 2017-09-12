#include "editor/views/scene_views/game_component_view.h"

#include <editor/views/scene_views/movable_object_view.h>
#include <editor/views/scene_views/game_component_views/camera_view.h>
#include <editor/views/scene_views/game_component_views/light_view.h>
#include <editor/views/scene_views/game_component_views/render_object_view.h>

#include <game/game_component.h>

#include <game/components/render/render_component.h>
#include <game/components/cameras/camera_component.h>
#include <graphics/lighting/light_source.h>

namespace ifx {

GameComponentView::GameComponentView(std::shared_ptr<SceneRenderer> scene_renderer) {
    movable_object_view_.reset(new MovableObjectView());

    camera_view_.reset(new CameraView());
    light_view_.reset(new LightView());
    render_object_view_.reset(new RenderObjectView(scene_renderer));
}

void GameComponentView::Render(std::shared_ptr<GameComponent> game_component) {
    movable_object_view_->Render(
        std::dynamic_pointer_cast<Transformable>(game_component));

    switch (game_component->type()) {
        case GameComponentType::LIGHT:
            light_view_->Render(
                std::dynamic_pointer_cast<LightSource>(game_component));
            break;
        case GameComponentType::RENDER:
            render_object_view_->Render(
                std::dynamic_pointer_cast<RenderComponent>(game_component));
            break;
        case GameComponentType::CAMERA:
            camera_view_->Render(
                std::dynamic_pointer_cast<CameraComponent>(game_component));
            break;
        default:return;
    }
}

}