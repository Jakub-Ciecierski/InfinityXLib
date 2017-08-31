#ifndef PROJECT_SOFT_BODY_SETTINGS_VIEW_H
#define PROJECT_SOFT_BODY_SETTINGS_VIEW_H

#include <string>

#include <RTFEM/FEM/Meshing/Tetrahedralization.h>

namespace ifx {

struct SoftBodyRenderingEffects;
struct SoftBodyObjects;

class RenderingEffect;
class RenderComponent;

class SoftBodySettingsView {
public:
    SoftBodySettingsView() = default;
    ~SoftBodySettingsView() = default;

    const rtfem::TetrahedralizationOptions& rtfem_options(){
        return rtfem_options_;}

    void Render(SoftBodyObjects& soft_body_objects,
                SoftBodyRenderingEffects& rendering_effects);
private:
    void RenderShow(SoftBodyRenderingEffects& rendering_effects,
                    SoftBodyObjects& soft_body_objects);
    void RenderShowRenderingEffects(
            SoftBodyRenderingEffects& rendering_effects);
    void RenderShowRenderingEffectCheckbox(std::string name,
                                           RenderingEffect &rendering_effect);

    void RenderShowObjects(SoftBodyObjects& soft_body_objects);
    void RenderShowObjectCheckbox(std::string name,
                                  RenderComponent& render_component);

    void RenderMeshingSettings();

    rtfem::TetrahedralizationOptions rtfem_options_;
};

}

#endif //PROJECT_SOFT_BODY_SETTINGS_VIEW_H
