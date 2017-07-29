#include "graphics/rendering/shadows/shadow_mapping_renderer.h"

#include <graphics/rendering/window/window.h>
#include <graphics/rendering/scene_renderer.h>
#include <graphics/rendering/fbo_rendering/fbo_renderer.h>

#include <graphics/lighting/types/light_directional.h>
#include <graphics/lighting/light_group.h>

#include <GL/glew.h>

namespace ifx{

ShadowMappingRenderer::ShadowMappingRenderer(
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<Window> window) :
        scene_renderer_(scene_renderer),
        window_(window){}

ShadowMappingRenderer::~ShadowMappingRenderer(){}

void ShadowMappingRenderer::Render(std::shared_ptr<FBORenderer> fbo_renderer){

    auto lights = scene_renderer_->light_group()->GetDirectionalLights();
    for(auto& light : lights){
        light->RenderToShadowMap(scene_renderer_);
    }

    // Shadow mapping binds its own FBO
    if(fbo_renderer)
        fbo_renderer->Bind();

    glViewport(0, 0, *(window_->width()), *(window_->height()));
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    scene_renderer_->Render();
}

}