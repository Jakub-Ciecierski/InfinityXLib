#include "game/game_component.h"

namespace ifx{

GameComponent::GameComponent(GameComponentType type) :
        type_(type){}

// static
std::string GameComponent::GetTypeString(GameComponentType type){
    switch(type){
        case GameComponentType::CAMERA:
            return "Camera";
        case GameComponentType::RENDER:
            return "Render";
        case GameComponentType::LIGHT:
            return "Light";
        case GameComponentType::PHYSICS:
            return "Rigid Body";
    }
    return "Unknown";
}

}