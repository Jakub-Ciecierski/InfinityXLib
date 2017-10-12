#ifndef PROJECT_SOFT_BODY_MESHING_VIEW_H
#define PROJECT_SOFT_BODY_MESHING_VIEW_H

#include <memory>

namespace ifx {

class SoftBodyMeshingCreationView;
class SoftBodyMeshingSettingsView;
class SoftBodyMeshingInfoView;

class ResourceManager;

struct SoftBodyObjects;
struct SoftBodyRenderingEffects;

class SoftBodyMeshingView {
public:
    SoftBodyMeshingView(std::shared_ptr<ResourceManager> resource_manager);
    ~SoftBodyMeshingView() = default;

    bool Render(SoftBodyObjects &soft_body_objects,
                SoftBodyRenderingEffects &rendering_effects);
private:
    void RenderSettings();
    bool RenderCreation(SoftBodyObjects &soft_body_objects,
                        SoftBodyRenderingEffects &rendering_effects);
    void RenderInfo();

    std::unique_ptr<SoftBodyMeshingCreationView> creation_view_;
    std::unique_ptr<SoftBodyMeshingSettingsView> settings_view_;
    std::unique_ptr<SoftBodyMeshingInfoView> info_view_;

};

}

#endif //PROJECT_SOFT_BODY_MESHING_VIEW_H
