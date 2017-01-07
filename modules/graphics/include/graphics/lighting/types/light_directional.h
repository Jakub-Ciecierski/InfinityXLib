#ifndef DUCK_LIGHT_DIRECTIONAL_H
#define DUCK_LIGHT_DIRECTIONAL_H

#include "graphics/lighting/light_source.h"

namespace ifx {
/*
 * Directional Light has a lookAt position which is used
 * to compute a direction.
 *
 * It binds the position and the direction with the shader.
 */
class LightDirectional : public LightSource {
public:

    LightDirectional(const LightParams& light_params);
    ~LightDirectional();

    glm::mat4 GetLightSpaceMatrix();
protected:
    virtual void bind(const Program &program, int id = -1) override;
};
}

#endif //DUCK_LIGHT_DIRECTIONAL_H
