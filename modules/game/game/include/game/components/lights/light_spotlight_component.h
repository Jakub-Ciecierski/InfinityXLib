#ifndef PROJECT_LIGHT_SPOTLIGHT_COMPONENT_H
#define PROJECT_LIGHT_SPOTLIGHT_COMPONENT_H

#include <game/game_component.h>
#include <graphics/lighting/types/light_spotlight.h>

namespace ifx {

class LightSpotlightComponent : public GameComponent, public LightSpotlight{
public:

    LightSpotlightComponent(const LightParams& light_params);

    ~LightSpotlightComponent();

private:
};
}

#endif //PROJECT_LIGHT_SPOTLIGHT_COMPONENT_H
