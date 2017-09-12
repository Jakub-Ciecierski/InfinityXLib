#include "game/components/lights/light_point_component.h"

namespace ifx {

LightPointComponent::LightPointComponent(const LightParams &light_params) :
    GameComponent(GameComponentType::LIGHT),
    LightPoint(light_params) {}

LightPointComponent::~LightPointComponent() {}

}