#include "engine_gui/views/scene_view/game_component_view.h"

#include <engine_gui/views/scene_view/movable_object_view.h>
#include <engine_gui/views/scene_view/game_component_views/camera_view.h>
#include <engine_gui/views/scene_view/game_component_views/light_view.h>
#include <engine_gui/views/scene_view/game_component_views/render_object_view.h>
#include "engine_gui/views/scene_view/game_component_views/rigid_body_view.h"

#include <object/movable_object.h>
#include <object/game_component.h>

#include <graphics/lighting/light_source.h>
#include <object/render_object.h>
#include <graphics/rendering/camera/camera.h>

#include <physics/rigid_body.h>

namespace ifx{

GameComponentView::GameComponentView(){
    movable_object_view_.reset(new MovableObjectView());

    camera_view_.reset(new CameraView());
    light_view_.reset(new LightView());
    render_object_view_.reset(new RenderObjectView());
    rigid_body_view_.reset(new RigidBodyView());
}
GameComponentView::~GameComponentView(){}

void GameComponentView::Render(std::shared_ptr<GameComponent> game_component){
    movable_object_view_->Render(game_component);

    switch(game_component->type()){
        case GameComponentType::LIGHT:
            light_view_->Render(
                    std::static_pointer_cast<LightSource>(game_component));
            break;
        case GameComponentType::RENDER:
            render_object_view_->Render(
                    std::static_pointer_cast<RenderObject>(game_component));
            break;
        case GameComponentType::CAMERA:
            camera_view_->Render(
                    std::static_pointer_cast<Camera>(game_component));
            break;
        case GameComponentType::PHYSICS:
            rigid_body_view_->Render(
                    std::static_pointer_cast<RigidBody>(game_component));
            break;
    }
}

}