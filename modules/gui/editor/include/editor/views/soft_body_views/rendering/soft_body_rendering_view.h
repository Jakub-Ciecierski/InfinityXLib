#ifndef PROJECT_SOFT_BODY_RENDERING_VIEW_H
#define PROJECT_SOFT_BODY_RENDERING_VIEW_H

#include <string>

namespace ifx {

struct SoftBodyRenderingEffects;
struct SoftBodyObjects;

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

    void Render(SoftBodyObjects &soft_body_objects,
                SoftBodyRenderingEffects &rendering_effects);

    void SetRenderObjectMode(RenderObjectMode mode);
private:
    void RenderShowRenderingEffects(
        SoftBodyRenderingEffects &rendering_effects);
    void RenderShowRenderingEffectCheckbox(std::string name,
                                           RenderingEffect &rendering_effect);
    void RenderShowObjects(SoftBodyObjects &soft_body_objects);

    RenderObjectSettings render_object_settings_;

};

}

#endif //PROJECT_SOFT_BODY_RENDERING_VIEW_H
