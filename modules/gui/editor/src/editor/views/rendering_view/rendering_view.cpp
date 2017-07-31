#include "editor/views/rendering_view/rendering_view.h"

#include <editor/processes/rendering_effect_processor.h>

namespace ifx {

RenderingView::RenderingView(
        std::shared_ptr<RenderingEffectProcessor> rendering_effect_processor) :
        View("Rendering"),
        rendering_effect_processor_(rendering_effect_processor){}

void RenderingView::Render(){

}

}