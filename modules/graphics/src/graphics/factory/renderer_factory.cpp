#include "graphics/factory/renderer_factory.h"

#include <graphics/rendering/renderer.h>

namespace ifx {

std::shared_ptr<Renderer> RendererFactory::Create(
    std::shared_ptr<Window> window,
    std::shared_ptr<RenderingContext> rendering_context,
    std::shared_ptr<TextureCreator> texture_creator,
    std::shared_ptr<ProgramCreator> program_creator,
    std::shared_ptr<ResourceManager> resource_manager) {
    if (!window || !rendering_context) {
        throw std::invalid_argument(
            "Creating Renderer System: Missing Dependencies");
    }

    auto renderer = std::shared_ptr<ifx::Renderer>(new ifx::Renderer(
        window, rendering_context));

    return renderer;
}

}