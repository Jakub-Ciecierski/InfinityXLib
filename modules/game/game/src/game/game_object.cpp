#include "game/game_object.h"

#include <game/scene_distributor.h>
#include <game/game_component.h>

namespace ifx{

GameObject::GameObject(std::shared_ptr<SceneDistributor> scene_distributor) :
        scene_distributor_(scene_distributor){}

GameObject::~GameObject(){}

void GameObject::Update(float time_delta){
    Transformable::Update();

    for(auto& component : components_){
        auto game_component_transformable
                = std::dynamic_pointer_cast<Transformable>(component);
        if(game_component_transformable)
            game_component_transformable->Update(time_delta);
    }
}

void GameObject::Add(std::shared_ptr<GameComponent> game_component){
    if(Exists(game_component))
        return;

    auto game_component_transformable
            = std::dynamic_pointer_cast<Transformable>(game_component);
    if(game_component_transformable)
        game_component_transformable->SetParent(this);

    components_.push_back(game_component);

    if(scene_distributor_)
        scene_distributor_->Add(game_component);
}

bool GameObject::Remove(std::shared_ptr<GameComponent> game_component){
    for(unsigned int i = 0; i < components_.size(); i++){
        if(components_[i] == game_component){
            if(scene_distributor_)
                scene_distributor_->Remove(game_component);
            components_.erase(components_.begin() + i);
            return true;
        }
    }
    return false;
}

std::vector<std::shared_ptr<GameComponent>>
        GameObject::GetComponents(const GameComponentType&& type){
    std::vector<std::shared_ptr<GameComponent>> out_components;
    for(auto& component : components_){
        if(component->type() == type){
            out_components.push_back(component);
        }
    }
    return out_components;
}

std::vector<std::shared_ptr<GameComponent>>& GameObject::GetComponents(){
    return components_;
}

bool GameObject::Exists(std::shared_ptr<GameComponent> game_component){
    for(unsigned int i = 0; i < components_.size(); i++){
        if(components_[i] == game_component){
            return true;
        }
    }
    return false;
}

}