#include "game/components/lights/light_directional_component.h"

#include <graphics/lighting/light_source.h>


namespace ifx{

LightDirectionalComponent::LightDirectionalComponent(
        const LightParams& light_params) :
        GameComponent(GameComponentType::LIGHT),
        LightDirectional(light_params){}

LightDirectionalComponent::~LightDirectionalComponent(){}

}