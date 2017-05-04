#include "game/components/lights/light_directional_component.h"

#include <graphics/lighting/light_source.h>


namespace ifx{

LightDirectionalComponent::LightDirectionalComponent(
        const LightParams& light_params,
        std::shared_ptr<ShadowMapping> shadow_mapping) :
        GameComponent(GameComponentType::LIGHT),
        LightDirectional(light_params, shadow_mapping){}

LightDirectionalComponent::~LightDirectionalComponent(){}

}