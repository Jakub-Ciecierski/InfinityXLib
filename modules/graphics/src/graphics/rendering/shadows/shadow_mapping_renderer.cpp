#include "graphics/rendering/shadows/shadow_mapping_renderer.h"

#include <graphics/rendering/window/window.h>
#include <graphics/rendering/scene_renderer.h>

#include <graphics/lighting/types/light_directional.h>
#include <graphics/lighting/light_group.h>

namespace ifx{

ShadowMappingRenderer::ShadowMappingRenderer(
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<Window> window) :
        scene_renderer_(scene_renderer),
        window_(window){}

ShadowMappingRenderer::~ShadowMappingRenderer(){}

void ShadowMappingRenderer::Render(){
    auto lights = scene_renderer_->light_group()->GetDirectionalLights();
    for(auto& light : lights){
        light->RenderToShadowMap(scene_renderer_);
    }
}

}