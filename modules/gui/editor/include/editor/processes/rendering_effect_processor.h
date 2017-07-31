#ifndef PROJECT_RENDERING_EFFECT_PROCESSOR_H
#define PROJECT_RENDERING_EFFECT_PROCESSOR_H

#include <memory>

namespace ifx {

class ResourceContext;
class SceneRenderer;

class RenderingEffectProcessor {
public:
    RenderingEffectProcessor(std::shared_ptr<ResourceContext> resource_context,
                             std::shared_ptr<SceneRenderer> scene_renderer);
    ~RenderingEffectProcessor() = default;

    void CompileAllPrograms();

private:
    std::shared_ptr<ResourceContext> resource_context_;
    std::shared_ptr<SceneRenderer> scene_renderer_;

};
}

#endif //PROJECT_RENDERING_EFFECT_PROCESSOR_H
