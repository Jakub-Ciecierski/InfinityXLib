#include "engine_gui/views/scene_view/game_object_view.h"

namespace ifx{

GameObjectView::GameObjectView(){}
GameObjectView::~GameObjectView(){}

void GameObjectView::Render(std::shared_ptr<GameObject> game_object){
    if(!game_object) return;
}

}