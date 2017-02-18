#ifndef DUCK_LIGHT_DIRECTIONAL_H
#define DUCK_LIGHT_DIRECTIONAL_H

#include "graphics/lighting/light_source.h"

namespace ifx {

class ShadowMapping;
class SceneRenderer;

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

    std::shared_ptr<ShadowMapping> shadow_mapping(){return shadow_mapping_;}

    void RenderToShadowMap(const std::shared_ptr<SceneRenderer> scene);

protected:
    virtual void bind(const Program &program, int id = -1) override;

    std::shared_ptr<ShadowMapping> shadow_mapping_;
};
}

#endif //DUCK_LIGHT_DIRECTIONAL_H
