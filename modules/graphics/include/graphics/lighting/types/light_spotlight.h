#ifndef DUCK_LIGHT_SPOTLIGHT_H
#define DUCK_LIGHT_SPOTLIGHT_H

#include <graphics/lighting/types/light_directional.h>

namespace ifx {

class ShadowMapping;

/*
 * Represents Flashlight
 * Binds the cutOff angle with the shader
 */
class LightSpotlight : public LightDirectional {
protected:
    virtual void bind(const Program &program, int id = -1) override;

public:
    LightSpotlight(const LightParams &light_params,
                   std::shared_ptr<ShadowMapping> shadow_mapping);
    ~LightSpotlight();
};
}

#endif //DUCK_LIGHT_SPOTLIGHT_H
