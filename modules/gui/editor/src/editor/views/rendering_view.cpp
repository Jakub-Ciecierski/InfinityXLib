#include "editor/views/rendering_view.h"

#include <editor/processes/rendering_effect_processor.h>
#include <editor/views/rendering_views/rendering_effect_view.h>

#include <graphics/rendering/scene_renderer.h>

#include <gui/imgui/imgui.h>
#include <common/unique_ptr.h>

namespace ifx {

RenderingView::RenderingView(
        std::shared_ptr<RenderingEffectProcessor> rendering_effect_processor) :
        View("Rendering"),
        rendering_effect_processor_(rendering_effect_processor){
    rendering_effect_view_ = ifx::make_unique<RenderingEffectView>(
            rendering_effect_processor);
}

void RenderingView::Render(){
    rendering_effect_view_->Render(
            rendering_effect_processor_->scene_renderer()->rendering_effects()
    );
}

}