#include "game/components/render/render_component.h"

namespace ifx {

RenderComponent::RenderComponent(std::shared_ptr<Model> model) :
    GameComponent(GameComponentType::RENDER),
    RenderObject(model) {}

RenderComponent::RenderComponent(std::vector<std::shared_ptr<Model>> models) :
    GameComponent(GameComponentType::RENDER),
    RenderObject(models) {}

RenderComponent::RenderComponent(const RenderComponent& other) :
        GameComponent(type()),
        RenderObject(other){

}

}