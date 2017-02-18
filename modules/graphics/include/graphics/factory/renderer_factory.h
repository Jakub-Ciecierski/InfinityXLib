#ifndef PROJECT_RENDERER_FACTORY_H
#define PROJECT_RENDERER_FACTORY_H

#include <memory>

namespace ifx {

class Renderer;
class FBORenderer;
class Window;
class ShadowMapping;

class RendererFactory {
public:
    RendererFactory();
    ~RendererFactory();

    virtual std::shared_ptr<Renderer> Create();
};
}

#endif //PROJECT_RENDERER_FACTORY_H
