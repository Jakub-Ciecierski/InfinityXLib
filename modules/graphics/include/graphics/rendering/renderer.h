#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

#include <controls/event_handler.h>
#include <graphics/rendering/window/window.h>

#include <memory>

namespace ifx {

class FBORenderer;
class GUI;
class SceneRenderer;
class ShadowMappingRenderer;

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
class Renderer : public EventHandler{
public:
    Renderer();
    ~Renderer();

    Window* window()  {return window_.get();}
    RenderingType rendering_type(){return rendering_type_;}
    std::shared_ptr<SceneRenderer> scene_renderer(){return scene_renderer_;}

    // Overridden from EventHandler.
    void HandleEvents() override;
    void Render();

    void SetGUI(std::shared_ptr<GUI> gui);
    void SetRenderingType(RenderingType type);

    void LimitFPS(bool val);
private:
    void initGLFWRenderContext();
    void initOpenGLContext();
    void initGLFWCallbacks();

    void RenderToScreen();
    void RenderToFBOTexture();

    std::shared_ptr<Window> window_;
    std::shared_ptr<GUI> gui_;

    RenderingType rendering_type_;

    std::shared_ptr<FBORenderer> fbo_renderer_;

    std::shared_ptr<SceneRenderer> scene_renderer_;

    std::shared_ptr<ShadowMappingRenderer> shadow_mapping_renderer_;
};

}
#endif //PROJECT_RENDERER_H
