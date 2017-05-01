#include "game/components/lights/light_spotlight_component.h"

namespace ifx{

LightSpotlightComponent::LightSpotlightComponent(
        const LightParams& light_params) :
        GameComponent(GameComponentType::LIGHT),
        LightSpotlight(light_params){}

LightSpotlightComponent::~LightSpotlightComponent(){}

}