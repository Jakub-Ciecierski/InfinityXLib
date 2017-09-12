#ifndef PROJECT_RENDERER_FACTORY_H
#define PROJECT_RENDERER_FACTORY_H

#include <memory>

namespace ifx {

class Renderer;
class Window;
class RenderingContext;
class TextureCreator;
class ProgramCreator;
class ResourceManager;

class RendererFactory {
public:
    RendererFactory() = default;
    virtual ~RendererFactory() = default;

    virtual std::shared_ptr<Renderer> Create(
        std::shared_ptr<Window> window,
        std::shared_ptr<RenderingContext> rendering_context,
        std::shared_ptr<TextureCreator> texture_creator,
        std::shared_ptr<ProgramCreator> program_creator,
        std::shared_ptr<ResourceManager> resource_manager);
};
}

#endif //PROJECT_RENDERER_FACTORY_H
