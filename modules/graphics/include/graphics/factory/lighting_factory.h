#ifndef PROJECT_LIGHTING_FACTORY_H
#define PROJECT_LIGHTING_FACTORY_H

#include <graphics/lighting/types/light_directional.h>
#include <graphics/lighting/types/light_point.h>
#include <graphics/lighting/types/light_spotlight.h>
#include <graphics/rendering/camera/camera.h>

#include <memory>

namespace ifx {
/*
 * Loads specific lights to the system
 */
class LightingFactory {
private:

public:

    LightingFactory();
    ~LightingFactory();

    std::shared_ptr<ifx::LightPoint> CreatePointLight();
    std::shared_ptr<ifx::LightDirectional> CreateDirectionalLight();
    std::shared_ptr<ifx::LightSpotlight> CreateSpotLight();

};
}

#endif //PROJECT_LIGHTING_FACTORY_H
