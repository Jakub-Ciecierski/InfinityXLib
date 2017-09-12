#ifndef PROJECT_LIGHT_COMPONENT_FACTORY_H
#define PROJECT_LIGHT_COMPONENT_FACTORY_H

#include <memory>

namespace ifx {

class LightPointComponent;
class LightSpotlightComponent;
class LightDirectionalComponent;

class TextureCreator;
class ProgramCreator;

class ShadowMapping;

class LightComponentFactory {
public:

    LightComponentFactory() = default;
    ~LightComponentFactory() = default;

    std::shared_ptr<LightPointComponent> CreatePointLight();
    std::shared_ptr<LightDirectionalComponent> CreateDirectionalLight(
        std::shared_ptr<TextureCreator> texture_creator,
        std::shared_ptr<ProgramCreator> program_creator);
    std::shared_ptr<LightSpotlightComponent> CreateSpotLight(
        std::shared_ptr<TextureCreator> texture_creator,
        std::shared_ptr<ProgramCreator> program_creator);

private:
    std::shared_ptr<ShadowMapping> CreateShadowMapping(
        std::shared_ptr<TextureCreator> texture_creator,
        std::shared_ptr<ProgramCreator> program_creator);
};
}

#endif //PROJECT_LIGHT_COMPONENT_FACTORY_H
