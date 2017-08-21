#include "graphics/rendering/renderer.h"

#include <graphics/shaders/program.h>
#include <graphics/rendering/scene_renderer.h>

#include <resources/resource_memory_cache.h>
#include <graphics/rendering/shadows/shadow_mapping_renderer.h>
#include <graphics/shaders/textures/texture_activator.h>
#include <graphics/shaders/loaders/program_loader.h>

#include <GL/glew.h>

namespace ifx {

Renderer::Renderer(std::shared_ptr<Window> window,
                   std::shared_ptr<RenderingContext> rendering_context) :
    window_(window),
    rendering_context_(rendering_context){
    scene_renderer_ = std::make_shared<SceneRenderer>();
    shadow_mapping_renderer_ = std::make_shared<ShadowMappingRenderer>(
            scene_renderer_, window_);
}

void Renderer::Update(float){
    TextureActivator::GetInstance().ResetGlobal();

    Render();
}

void Renderer::Render(){
    shadow_mapping_renderer_->Render();

    RenderScene();
}

void Renderer::RenderScene(){
    glViewport(0, 0, *(window_->width()), *(window_->height()));
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_MULTISAMPLE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    scene_renderer_->Render();
}

}