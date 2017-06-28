#include "graphics/rendering/renderer.h"

#include <graphics/shaders/program.h>
#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/rendering/scene_renderer.h>

#include <resources/resource_memory_cache.h>
#include <graphics/rendering/shadows/shadow_mapping_renderer.h>
#include <graphics/shaders/textures/texture_activator.h>
#include <graphics/shaders/loaders/program_loader.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

namespace ifx {

Renderer::Renderer(std::shared_ptr<Window> window,
                   std::shared_ptr<RenderingContext> rendering_context) :
    rendering_type_(RenderingType::NORMAL),
    fbo_renderer_(nullptr),
    window_(window),
    rendering_context_(rendering_context){


    // TODO Don't create them here
    scene_renderer_ = std::shared_ptr<SceneRenderer>(new SceneRenderer());
    shadow_mapping_renderer_ = std::shared_ptr<ShadowMappingRenderer>
            (new ShadowMappingRenderer(scene_renderer_,
                                       window_));

    // TODO fbo
/*
    fbo_renderer_
            = std::shared_ptr<FBORenderer>(new FBORenderer(window_.get()));

    ifx::Resources& resources = ifx::Resources::GetInstance();
    std::string vertex_path =
            resources.GetResourcePath("fbo/fbo.vs", ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("fbo/fbo.fs", ifx::ResourceType::SHADER);
    auto program = ProgramLoader().CreateProgram(vertex_path, fragment_path);
    fbo_renderer_->SetProgram(program);
*/
}

Renderer::~Renderer(){
    // TODO Resources requires GL context
    // TODO
    //ResourceMemoryCache::GetInstance().ClearAll();
}

void Renderer::SetRenderingType(RenderingType type){
    rendering_type_ = type;
}

void Renderer::Update(float){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    TextureActivator::GetInstance().ResetGlobal();

    switch(rendering_type_){
        case RenderingType::NORMAL:
            RenderToScreen();
            break;
        case RenderingType::FBO_TEXTURE:
            RenderToFBOTexture();
            break;
    }
}

void Renderer::RenderToScreen(){
    shadow_mapping_renderer_->Render(nullptr);
}

void Renderer::RenderToFBOTexture(){
    shadow_mapping_renderer_->Render(fbo_renderer_);

    // Second Pass
    fbo_renderer_->Render();
}

}