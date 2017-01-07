#include "game/scene_container.h"

#include <object/game_object.h>
#include <game/scene_distributor.h>

namespace ifx{

SceneContainer::SceneContainer(
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<PhysicsSimulation> physics_simulation){
    scene_distributor_ = std::shared_ptr<SceneDistributor>(
            new SceneDistributor(scene_renderer, physics_simulation));
}
SceneContainer::~SceneContainer(){}

void SceneContainer::Update(){
    for(auto& object : game_objects_){
        object->update();
    }
}

void SceneContainer::Add(std::shared_ptr<GameObject> game_object){
    OnAdd(game_object);

    game_objects_.push_back(game_object);
}

bool SceneContainer::Remove(std::shared_ptr<GameObject> game_object){
    OnRemove(game_object);

    for(unsigned int i = 0; i < game_objects_.size(); i++){
        if(game_objects_[i] == game_object){
            game_objects_.erase(game_objects_.begin() + i);
            return true;
        }
    }
    return false;
}

void SceneContainer::OnAdd(std::shared_ptr<GameObject> game_object){
    if(scene_distributor_)
        scene_distributor_->Add(game_object);
}

bool SceneContainer::OnRemove(std::shared_ptr<GameObject> game_object){
    if(scene_distributor_)
        return scene_distributor_->Remove(game_object);
    return false;
}

}