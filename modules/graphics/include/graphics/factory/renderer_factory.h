#ifndef PROJECT_RENDERER_FACTORY_H
#define PROJECT_RENDERER_FACTORY_H

#include <memory>

namespace ifx {

class Renderer;
class Window;
class RenderingContext;

class RendererFactory {
public:
    RendererFactory();
    ~RendererFactory();

    virtual std::shared_ptr<Renderer> Create(
            std::shared_ptr<Window> window,
            std::shared_ptr<RenderingContext> rendering_context);
};
}

#endif //PROJECT_RENDERER_FACTORY_H
