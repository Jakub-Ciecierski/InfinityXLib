#ifndef PROJECT_LIGHT_POINT_COMPONENT_H
#define PROJECT_LIGHT_POINT_COMPONENT_H

#include <game/game_component.h>
#include <graphics/lighting/types/light_point.h>

namespace ifx {

class LightPointComponent : public GameComponent, LightPoint{
public:

    LightPointComponent(const LightParams& light_params);

    ~LightPointComponent();

private:
};
}

#endif //PROJECT_LIGHT_POINT_COMPONENT_H
