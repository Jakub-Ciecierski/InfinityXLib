#ifndef PROJECT_LIGHT_COMPONENT_FACTORY_H
#define PROJECT_LIGHT_COMPONENT_FACTORY_H

#include <memory>

namespace ifx {

class LightPointComponent;
class LightSpotlightComponent;
class LightDirectionalComponent;

class LightComponentFactory {
public:

    LightComponentFactory();

    ~LightComponentFactory();

    std::shared_ptr<LightPointComponent> CreatePointLight();
    std::shared_ptr<LightDirectionalComponent> CreateDirectionalLight();
    std::shared_ptr<LightSpotlightComponent> CreateSpotLight();

private:
};
}

#endif //PROJECT_LIGHT_COMPONENT_FACTORY_H
