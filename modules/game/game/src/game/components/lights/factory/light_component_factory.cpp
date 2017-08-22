#include "game/components/lights/factory/light_component_factory.h"

#include <game/components/lights/light_directional_component.h>
#include <game/components/lights/light_point_component.h>
#include <game/components/lights/light_spotlight_component.h>

#include <graphics/rendering/shadows/shadow_mapping.h>
#include <graphics/shaders/loaders/program_loader.h>
#include <graphics/shaders/textures/texture_creator.h>

#include <resources/resource_manager.h>

namespace ifx{

std::shared_ptr<LightPointComponent>
LightComponentFactory::CreatePointLight(){
    LightParams light;

    auto light_source = std::make_shared<LightPointComponent>(light);

    return light_source;
}

std::shared_ptr<LightDirectionalComponent>
LightComponentFactory::CreateDirectionalLight(
        std::shared_ptr<TextureCreator> texture_creator,
        std::shared_ptr<ProgramCreator> program_creator){
    ifx::LightParams light;

    auto light_source = std::make_shared<ifx::LightDirectionalComponent>(
                    light,
                    CreateShadowMapping(texture_creator, program_creator));

    light_source->rotateTo(glm::vec3(0, 270, 0));
    light_source->LookAt(glm::vec3(0,0,0));

    return light_source;
}

std::shared_ptr<LightSpotlightComponent>
LightComponentFactory::CreateSpotLight(
        std::shared_ptr<TextureCreator> texture_creator,
        std::shared_ptr<ProgramCreator> program_creator){
    ifx::LightParams light;

    auto light_source = std::make_shared<ifx::LightSpotlightComponent>(
                    light,
                    CreateShadowMapping(texture_creator, program_creator));

    light_source->rotateTo(glm::vec3(0, 270, 0));
    light_source->LookAt(glm::vec3(0,0,0));

    return light_source;
}

std::shared_ptr<ShadowMapping> LightComponentFactory::CreateShadowMapping(
        std::shared_ptr<TextureCreator> texture_creator,
        std::shared_ptr<ProgramCreator> program_creator){
    auto resource_path = texture_creator->resource_manager()->resource_path();

    std::string vertex_path = resource_path->GetResourcePath(
                    "engine/shadow_mapping.prog/shadow_mapping.vs",
                    ifx::ResourceType::SHADER);
    std::string fragment_path = resource_path->GetResourcePath(
                    "engine/shadow_mapping.prog/shadow_mapping.fs",
                    ifx::ResourceType::SHADER);
    auto program = ProgramLoader(program_creator).CreateProgram(
            vertex_path, fragment_path);
    return std::shared_ptr<ShadowMapping>(
            new ShadowMapping(
                    Dimensions{4024, 4024}, program, texture_creator));
}

}