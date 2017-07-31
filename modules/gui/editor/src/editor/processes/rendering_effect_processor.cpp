#include "editor/processes/rendering_effect_processor.h"

#include <game/resources/resource_context.h>
#include <graphics/rendering/scene_renderer.h>

namespace ifx {

RenderingEffectProcessor::RenderingEffectProcessor(
        std::shared_ptr<ResourceContext> resource_context,
        std::shared_ptr<SceneRenderer> scene_renderer) :
        resource_context_(resource_context),
        scene_renderer_(scene_renderer) {}

void RenderingEffectProcessor::CompileAllPrograms(){

}

}