#ifndef PROJECT_FBO_RENDERER2_H
#define PROJECT_FBO_RENDERER2_H

#include <graphics/rendering/renderer.h>
#include <graphics/rendering/window/window_observer.h>

namespace ifx {

class FBO;
class Mesh;
class Program;

class FBORenderer : public Renderer, public WindowObserver {
public:
    FBORenderer(std::shared_ptr<Window> window,
                std::shared_ptr<RenderingContext> rendering_context,
                std::unique_ptr<FBO> fbo,
                std::unique_ptr<FBO> intermediate_fbo,
                std::unique_ptr<Mesh> screen_mesh,
                std::shared_ptr<Program> program);

    ~FBORenderer();

    virtual void OnResize(int width, int height) override;
protected:
    virtual void Render() override;

private:
    void RenderBufferToScreenMesh();

    std::unique_ptr<FBO> fbo_;
    std::unique_ptr<FBO> intermediate_fbo_;
    std::unique_ptr<Mesh> screen_mesh_;
    std::shared_ptr<Program> program_;
};
}

#endif //PROJECT_FBO_RENDERER2_H
