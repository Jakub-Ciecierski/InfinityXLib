#ifndef PROJECT_SOFT_BODY_RENDERING_VIEW_H
#define PROJECT_SOFT_BODY_RENDERING_VIEW_H

#include <string>
#include <memory>

namespace ifx {

struct SoftBodyRenderingEffects;
struct SoftBodyEditorObjects;

class RenderingEffect;
class RenderComponent;

enum class RenderObjectMode {
    Output, Input
};

struct RenderObjectSettings {
    RenderObjectMode mode = RenderObjectMode::Input;
    bool show_input = true;
    bool show_output = false;
};

class SoftBodyRenderingView {
public:
    SoftBodyRenderingView();
    ~SoftBodyRenderingView() = default;

    void Render(std::shared_ptr<RenderComponent> triangle_mesh_render,
                std::shared_ptr<RenderComponent> fem_mesh_render,
                SoftBodyRenderingEffects &rendering_effects);

    void SetRenderObjectMode(RenderObjectMode mode);
    void UpdateRenderObjectMode(
        std::shared_ptr<RenderComponent> triangle_mesh_render,
        std::shared_ptr<RenderComponent> fem_mesh_render);
private:
    void RenderShowRenderingEffects(
        SoftBodyRenderingEffects &rendering_effects);
    void RenderShowRenderingEffectCheckbox(std::string name,
                                           RenderingEffect &rendering_effect);
    void RenderShowObjects(
        std::shared_ptr<RenderComponent> triangle_mesh_render,
        std::shared_ptr<RenderComponent> fem_mesh_render);

    RenderObjectSettings render_object_settings_;

};

}

#endif //PROJECT_SOFT_BODY_RENDERING_VIEW_H
