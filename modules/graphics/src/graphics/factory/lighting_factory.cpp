#include <graphics/lighting/light_group.h>
#include "graphics/factory/lighting_factory.h"

#include <memory>

namespace ifx {

LightingFactory::LightingFactory() {

}

LightingFactory::~LightingFactory() {

}

LightPoint *LightingFactory::loadPointLight() {
    LightParams light;
    light.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    light.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    light.constant = 1.0f;
    light.linear = 0.09f;
    light.quadratic = 0.0032;

    LightPoint *lightSource = new LightPoint(light);
    return lightSource;
}

LightDirectional *LightingFactory::loadDirLight() {
    LightParams light;

    light.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    LightDirectional *lightSource = new LightDirectional(light);

    lightSource->moveTo(glm::vec3(0.0f, 2.5f, 0.0f));
    lightSource->LookAt(glm::vec3(0,0,0));

    return lightSource;
}

LightSpotlight *LightingFactory::loadSpotlight() {
    LightParams light;
    //light.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    //light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.ambient = glm::vec3(0.9f, 0.9f, 0.9f);
    light.diffuse = glm::vec3(0.9f, 0.9f, 0.9f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    light.constant = 1.0f;
    light.linear = 0.09f;
    light.quadratic = 0.032;

    light.cutOff = 22.5f;
    light.outerCutOff = 27.5f;

    LightSpotlight *lightSource = new LightSpotlight(light);

    lightSource->LookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    return lightSource;
}

LightGroup* LightingFactory::createGroupLight(Camera* camera){
    LightGroup* light_group = new LightGroup();

    std::unique_ptr<LightDirectional> light(loadDirLight());
    light_group->Add(std::move(light));

    return light_group;
}

}