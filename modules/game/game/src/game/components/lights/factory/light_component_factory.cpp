#include "game/components/lights/factory/light_component_factory.h"

#include <game/components/lights/light_directional_component.h>
#include <game/components/lights/light_point_component.h>
#include <game/components/lights/light_spotlight_component.h>

namespace ifx{

LightComponentFactory::LightComponentFactory(){}

LightComponentFactory::~LightComponentFactory(){}

std::shared_ptr<LightPointComponent> LightComponentFactory::CreatePointLight(){
    LightParams light;

    auto light_source = std::shared_ptr<LightPointComponent>(
            new ifx::LightPointComponent(light));

    return light_source;
}

std::shared_ptr<LightDirectionalComponent>
LightComponentFactory::CreateDirectionalLight(){
    ifx::LightParams light;

    auto light_source = std::shared_ptr<ifx::LightDirectionalComponent>(
            new ifx::LightDirectionalComponent(light));
    light_source->rotateTo(glm::vec3(0, 270, 0));
    light_source->LookAt(glm::vec3(0,0,0));

    return light_source;
}

std::shared_ptr<LightSpotlightComponent>
LightComponentFactory::CreateSpotLight(){
    ifx::LightParams light;

    auto light_source = std::shared_ptr<ifx::LightSpotlightComponent>(
            new ifx::LightSpotlightComponent(light));
    light_source->rotateTo(glm::vec3(0, 270, 0));
    light_source->LookAt(glm::vec3(0,0,0));

    return light_source;
}


}