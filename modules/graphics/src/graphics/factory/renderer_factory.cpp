#include "graphics/factory/renderer_factory.h"

#include <graphics/rendering/renderer.h>

namespace ifx {

RendererFactory::RendererFactory() { }

RendererFactory::~RendererFactory() { }

std::shared_ptr<Renderer> RendererFactory::Create() {
    auto renderer = std::unique_ptr<ifx::Renderer>(new ifx::Renderer());

    return renderer;
}

}