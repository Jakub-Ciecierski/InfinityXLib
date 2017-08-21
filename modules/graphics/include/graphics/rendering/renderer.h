#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

#include <graphics/rendering/window/window.h>
#include <common/updatable.h>

#include <memory>

namespace ifx {

class SceneRenderer;
class ShadowMappingRenderer;
class Window;
class RenderingContext;


/**
 * Takes ownership over ShadowMapping
 */
class Renderer : public Updatable{
public:
    Renderer(std::shared_ptr<Window> window,
             std::shared_ptr<RenderingContext> rendering_context);
    virtual ~Renderer() = default;

    std::shared_ptr<Window> window()  {return window_;}
    std::shared_ptr<SceneRenderer> scene_renderer(){return scene_renderer_;}

    virtual void Update(float time_delta = 0) override;
protected:
    virtual void Render();
    void RenderScene();

    std::shared_ptr<Window> window_;

    std::shared_ptr<SceneRenderer> scene_renderer_;

    std::shared_ptr<ShadowMappingRenderer> shadow_mapping_renderer_;

    std::shared_ptr<RenderingContext> rendering_context_;
};

}
#endif //PROJECT_RENDERER_H
