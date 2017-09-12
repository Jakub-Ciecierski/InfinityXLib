#ifndef PROJECT_SHADOW_MAPPING_RENDERER_H
#define PROJECT_SHADOW_MAPPING_RENDERER_H

#include <memory>

namespace ifx {

class SceneRenderer;
class Window;

class ShadowMappingRenderer {
public:
    ShadowMappingRenderer(
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<Window> window);
    ~ShadowMappingRenderer();

    void Render();

private:
    std::shared_ptr<SceneRenderer> scene_renderer_;
    std::shared_ptr<Window> window_;
};
}

#endif //PROJECT_SHADOW_MAPPING_RENDERER_H
