#ifndef PROJECT_LIGHT_VIEW_H
#define PROJECT_LIGHT_VIEW_H

#include <memory>

namespace ifx {

class LightSource;
class LightDirectional;

class LightView{
public:

    LightView();
    ~LightView();

    void Render(std::shared_ptr<LightSource> light_source);
private:

    void RenderColor(std::shared_ptr<LightSource> light_source);
    void RenderColorAmbient(std::shared_ptr<LightSource> light_source);
    void RenderColorDiffuse(std::shared_ptr<LightSource> light_source);
    void RenderColorSpecular(std::shared_ptr<LightSource> light_source);

    void RenderAttenuation(std::shared_ptr<LightSource> light_source);
    void RenderAttenuationConstant(std::shared_ptr<LightSource> light_source);
    void RenderAttenuationLinear(std::shared_ptr<LightSource> light_source);
    void RenderAttenuationQuadratic(std::shared_ptr<LightSource> light_source);

    void RenderSpotlight(std::shared_ptr<LightSource> light_source);

    void RenderShadowMapping(std::shared_ptr<LightSource> light_source);
    void RenderShadowMappingProjectionParameters(
            std::shared_ptr<LightDirectional> light_source);
};
}

#endif //PROJECT_LIGHT_VIEW_H
