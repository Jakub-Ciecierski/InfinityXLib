#include "graphics/rendering/context/factory/rendering_context_opengl_factory.h"

#include <graphics/rendering/context/contexts/rendering_context_opengl.h>

namespace ifx {

RenderingContextOpenglFactory::RenderingContextOpenglFactory() {}

RenderingContextOpenglFactory::~RenderingContextOpenglFactory() {}

std::shared_ptr<RenderingContext> RenderingContextOpenglFactory::Create() {
    auto context = std::shared_ptr<RenderingContextOpengl>(
        new RenderingContextOpengl());
    return context;
}

}