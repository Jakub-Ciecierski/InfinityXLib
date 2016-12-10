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

    std::shared_ptr<Renderer> Create();

private:
    std::unique_ptr<FBORenderer> CreateFBORenderer(Window* window);
    std::unique_ptr<ShadowMapping> CreateShadowMapping();

};
}

#endif //PROJECT_RENDERER_FACTORY_H
