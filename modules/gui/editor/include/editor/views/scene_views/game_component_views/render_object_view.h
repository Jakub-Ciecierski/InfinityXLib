#ifndef PROJECT_RENDER_OBJECT_VIEW_H
#define PROJECT_RENDER_OBJECT_VIEW_H

#include <memory>

namespace ifx {

class RenderComponent;
class RenderingEffect;
class SceneRenderer;
class RenderObjectMaterialView;
class ResourceContext;

class RenderObjectView {
public:

    RenderObjectView(std::shared_ptr<SceneRenderer> scene_renderer,
                     std::shared_ptr<ResourceContext> resource_creator);
    ~RenderObjectView() = default;

    void Render(std::shared_ptr<RenderComponent> render_object);
private:
    void RenderRenderingEffects(std::shared_ptr<RenderComponent> render_object);
    void RenderRenderingEffectsContextMenu(std::shared_ptr<RenderComponent> render_object);
    void RenderList(std::shared_ptr<RenderComponent> render_object);
    void RenderRenderingEffectContextMenu(RenderingEffect *rendering_effect,
                                          std::shared_ptr<RenderComponent> render_object);

    std::string GetBaseName(const std::string &name);

    std::shared_ptr<SceneRenderer> scene_renderer_;

    std::unique_ptr<RenderObjectMaterialView> render_component_material_view_;
};
}

#endif //PROJECT_RENDER_OBJECT_VIEW_H
