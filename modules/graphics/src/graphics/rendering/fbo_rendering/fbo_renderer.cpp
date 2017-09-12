#include "graphics/rendering/fbo_rendering/fbo_renderer.h"

#include <graphics/shaders/buffers/fbo.h>
#include <graphics/model/mesh.h>
#include <graphics/rendering/shadows/shadow_mapping_renderer.h>
#include <graphics/rendering/scene_renderer.h>
#include <graphics/rendering/window/window.h>

#include <GL/glew.h>

namespace ifx {

FBORenderer::FBORenderer(
    std::shared_ptr<Window> window,
    std::shared_ptr<RenderingContext> rendering_context,
    std::unique_ptr<FBO> fbo,
    std::unique_ptr<FBO> intermediate_fbo,
    std::unique_ptr<Mesh> screen_mesh,
    std::shared_ptr<Program> program) :
    Renderer(window, rendering_context),
    fbo_(std::move(fbo)),
    intermediate_fbo_(std::move(intermediate_fbo)),
    screen_mesh_(std::move(screen_mesh)),
    program_(program),
    render_to_screen_(true) {
    if (!fbo_ || !screen_mesh_ || !program_) {
        throw std::invalid_argument(
            "FBORenderer2::FBORenderer2 - Invalid arguments");
    }
    window_->AddObserver(this);
}

FBORenderer::~FBORenderer() {
    window_->RemoveObserver(this);
}

void FBORenderer::EnableRenderToScreen(bool value) {
    render_to_screen_ = value;
}

const Texture2D &FBORenderer::GetSceneTexture() {
    return *intermediate_fbo_->texture();
}

void FBORenderer::Render() {
    shadow_mapping_renderer_->Render();

    fbo_->Bind();
    RenderScene();

    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo_->id());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediate_fbo_->id());
    glBlitFramebuffer(0, 0,
                      fbo_->texture()->width(),
                      fbo_->texture()->height(),
                      0, 0,
                      fbo_->texture()->width(),
                      fbo_->texture()->height(),
                      GL_COLOR_BUFFER_BIT,
                      GL_NEAREST);
    fbo_->Unbind();

    if (render_to_screen_)
        RenderFBOToScreen();
}

void FBORenderer::RenderFBOToScreen() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    screen_mesh_->draw(*program_);
}

void FBORenderer::OnResize(int width, int height) {
    fbo_->texture()->InitData(nullptr, width, height);
    fbo_->Compile();

    intermediate_fbo_->texture()->InitData(nullptr, width, height);
    intermediate_fbo_->Compile();
}

}
