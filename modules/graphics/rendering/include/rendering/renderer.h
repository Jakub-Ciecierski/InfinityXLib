#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

#include <controls/event_handler.h>
#include <rendering/scene/scene.h>
#include <rendering/window/window.h>
#include <rendering/shadows/shadow_mapping.h>

#include <memory>

namespace ifx {

class FBORenderer;
class GUI;

/**
 * Render to window directly or to texture.
 * Rendering to texture allow for post-processing.
 */
enum class RenderingType{
    NORMAL, FBO_TEXTURE
};

/**
 * Type of shadows to render.
 */
enum class ShadowsType{
    NONE, SHADOW_MAPPING
};

/**
 * Takes ownership over ShadowMapping
 */
class Renderer : public EventHandler{
public:
    Renderer();
    ~Renderer();

    std::shared_ptr<Scene> scene()  {return scene_;}
    Window* window()  {return window_.get();}
    RenderingType rendering_type(){return rendering_type_;}
    ShadowsType shadow_type(){return shadow_type_;};

    // Overridden from EventHandler.
    void HandleEvents() override;
    void Update();
    void Render();

    void SetScene(std::shared_ptr<Scene> scene);
    void SetGUI(std::unique_ptr<GUI> gui);
    void SetRenderingType(RenderingType type);
    void SetShadowsType(ShadowsType type);
    void SetFBORenderer(std::unique_ptr<FBORenderer> fbo_renderer);
    void SetShadowMapping(std::unique_ptr<ShadowMapping> shadow_mapping);

private:
    void initGLFWRenderContext();
    void initOpenGLContext();
    void initGLFWCallbacks();

    void RenderNormal();
    void RenderNormalNoShadow();
    void RenderNormalShadowMapping();
    void RenderFBOTexture();

    std::unique_ptr<Window> window_;
    std::shared_ptr<ifx::Scene> scene_;
    std::unique_ptr<GUI> gui_;

    RenderingType rendering_type_;
    ShadowsType shadow_type_;

    std::unique_ptr<FBORenderer> fbo_renderer_;
    std::unique_ptr<ShadowMapping> shadow_mapping_;
};

}
#endif //PROJECT_RENDERER_H
