#include "engine_gui/views/scene_view/game_object_view.h"

#include <views/scene_view/movable_object_view.h>

#include <game/scene_container.h>

#include <object/movable_object.h>
#include <object/game_object.h>
#include <object/game_component.h>
#include <gui/imgui/imgui.h>

namespace ifx{

GameObjectView::GameObjectView(){
    movable_object_view_.reset(new MovableObjectView());
}
GameObjectView::~GameObjectView(){}

void GameObjectView::Render(std::shared_ptr<GameObject> game_object,
                            std::shared_ptr<SceneContainer> scene){
    RenderRemove(game_object, scene);
    movable_object_view_->Render(game_object);
}

void GameObjectView::RenderRemove(std::shared_ptr<GameObject> game_object,
                                  std::shared_ptr<SceneContainer> scene){
    if(ImGui::Button("Remove")){
        scene->Remove(game_object);
    }
}


}