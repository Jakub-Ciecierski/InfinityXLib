#include "editor/views/scene_views/game_object_view.h"

#include <editor/views/scene_views/movable_object_view.h>

#include <game/game_object.h>

namespace ifx{

GameObjectView::GameObjectView(){
    movable_object_view_.reset(new MovableObjectView());
}
GameObjectView::~GameObjectView(){}

void GameObjectView::Render(std::shared_ptr<GameObject> game_object){
    movable_object_view_->Render(game_object);
}

}