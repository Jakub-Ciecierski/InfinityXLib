#ifndef PROJECT_LIGHT_DIRECTIONAL_COMPONENT_H
#define PROJECT_LIGHT_DIRECTIONAL_COMPONENT_H

#include <game/game_component.h>
#include <graphics/lighting/types/light_directional.h>

namespace ifx {

class ShadowMapping;

class LightDirectionalComponent : public LightDirectional,
                                  public GameComponent {
public:
    LightDirectionalComponent(const LightParams &light_params,
                              std::shared_ptr<ShadowMapping> shadow_mapping);

    ~LightDirectionalComponent() = default;

private:
};
}

#endif //PROJECT_LIGHT_DIRECTIONAL_COMPONENT_H
