#include "game/components/lights/light_spotlight_component.h"

namespace ifx {

LightSpotlightComponent::LightSpotlightComponent(
    const LightParams &light_params,
    std::shared_ptr<ShadowMapping> shadow_mapping) :
    GameComponent(GameComponentType::LIGHT),
    LightSpotlight(light_params, shadow_mapping) {}

LightSpotlightComponent::~LightSpotlightComponent() {}

}