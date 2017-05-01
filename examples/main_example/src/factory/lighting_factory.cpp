#include <graphics/lighting/light_group.h>
#include "factory/lighting_factory.h"

#include <memory>

namespace ifx {

LightingFactory::LightingFactory() {

}

LightingFactory::~LightingFactory() {

}

std::shared_ptr<ifx::LightPoint> LightingFactory::CreatePointLight(){
    LightParams light;

    auto light_source = std::shared_ptr<ifx::LightPoint>(
            new ifx::LightPoint(light));

    return light_source;
}

std::shared_ptr<ifx::LightDirectional> LightingFactory::CreateDirectionalLight(){
    ifx::LightParams light;

    auto light_source = std::shared_ptr<ifx::LightDirectional>(
            new ifx::LightDirectional(light));
    light_source->rotateTo(glm::vec3(0, 270, 0));
    light_source->LookAt(glm::vec3(0,0,0));

    return light_source;
}

std::shared_ptr<ifx::LightSpotlight> LightingFactory::CreateSpotLight(){
    ifx::LightParams light;

    auto light_source = std::shared_ptr<ifx::LightSpotlight>(
            new ifx::LightSpotlight(light));
    light_source->rotateTo(glm::vec3(0, 270, 0));
    light_source->LookAt(glm::vec3(0,0,0));

    return light_source;
}

}