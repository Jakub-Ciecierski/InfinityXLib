#include "object/game_object.h"

#include <object/game_component.h>

namespace ifx{

GameObject::GameObject(){}

GameObject::~GameObject(){}

void GameObject::update(){
    MovableObject::update();

    for(auto& component : components_)
        component->update();
}

void GameObject::Add(std::shared_ptr<GameComponent> game_component){
    game_component->SetParent(this);
    components_.push_back(game_component);
}

bool GameObject::Remove(std::shared_ptr<GameComponent> game_component){
    for(unsigned int i = 0; i < components_.size(); i++){
        if(components_[i] == game_component){
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

}