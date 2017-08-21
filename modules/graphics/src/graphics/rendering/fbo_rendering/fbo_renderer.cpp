#include "graphics/rendering/fbo_rendering/fbo_renderer.h"

#include <graphics/shaders/buffers/fbo.h>
#include <graphics/model/mesh.h>
#include <graphics/rendering/shadows/shadow_mapping_renderer.h>
#include <graphics/rendering/scene_renderer.h>

#include <GL/glew.h>

namespace ifx{

FBORenderer::FBORenderer(
        std::shared_ptr<Window> window,
        std::shared_ptr<RenderingContext> rendering_context,
        std::unique_ptr<FBO> fbo,
        std::unique_ptr<Mesh> screen_mesh,
        std::shared_ptr<Program> program) :
        Renderer(window, rendering_context),
        fbo_(std::move(fbo)),
        screen_mesh_(std::move(screen_mesh)),
        program_(program){
    if(!fbo_ || !screen_mesh_ || !program_){
        throw std::invalid_argument(
                "FBORenderer2::FBORenderer2 - Invalid arguments");
    }
    window_->AddObserver(this);
}

FBORenderer::~FBORenderer(){
    window_->RemoveObserver(this);
}

void FBORenderer::Render(){
    shadow_mapping_renderer_->Render();

    fbo_->Bind();
    RenderScene();

    RenderBufferToScreenMesh();
}

void FBORenderer::RenderBufferToScreenMesh(){
    glDisable(GL_DEPTH_TEST);
    fbo_->Unbind();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    screen_mesh_->draw(*program_);
}

void FBORenderer::OnResize(int width, int height) {
    fbo_->texture()->InitData(nullptr, width, height);
    fbo_->Compile();
}

}
