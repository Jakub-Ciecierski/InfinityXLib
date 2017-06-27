#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

#include <graphics/rendering/window/window.h>
#include <common/updatable.h>

#include <memory>

namespace ifx {

class FBORenderer;
class SceneRenderer;
class ShadowMappingRenderer;
class Window;
class RenderingContext;

/**
 * Render to window directly or to texture.
 * Rendering to texture allow for post-processing.
 */
enum class RenderingType{
    NORMAL, FBO_TEXTURE
};

/**
 * Takes ownership over ShadowMapping
 */
class Renderer : public Updatable{
public:
    Renderer(std::shared_ptr<Window> window,
             std::shared_ptr<RenderingContext> rendering_context);
    ~Renderer();

    Window* window()  {return window_.get();}
    RenderingType rendering_type(){return rendering_type_;}
    std::shared_ptr<SceneRenderer> scene_renderer(){return scene_renderer_;}

    virtual void Update(float time_delta = 0) override;

    void SetRenderingType(RenderingType type);
private:
    void RenderToScreen();
    void RenderToFBOTexture();

    std::shared_ptr<Window> window_;

    RenderingType rendering_type_;

    std::shared_ptr<FBORenderer> fbo_renderer_;

    std::shared_ptr<SceneRenderer> scene_renderer_;

    std::shared_ptr<ShadowMappingRenderer> shadow_mapping_renderer_;

    std::shared_ptr<RenderingContext> rendering_context_;
};

}
#endif //PROJECT_RENDERER_H
