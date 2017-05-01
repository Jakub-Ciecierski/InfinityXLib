#ifndef PROJECT_LIGHT_DIRECTIONAL_COMPONENT_H
#define PROJECT_LIGHT_DIRECTIONAL_COMPONENT_H

#include <game/game_component.h>
#include <graphics/lighting/types/light_directional.h>

namespace ifx {

class LightDirectionalComponent : public LightDirectional,
                                  public GameComponent {
public:

    LightDirectionalComponent(const LightParams& light_params);

    ~LightDirectionalComponent();

private:
};
}

#endif //PROJECT_LIGHT_DIRECTIONAL_COMPONENT_H
