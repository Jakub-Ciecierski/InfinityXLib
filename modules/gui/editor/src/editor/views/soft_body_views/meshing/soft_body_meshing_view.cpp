#include "editor/views/soft_body_views/meshing/soft_body_meshing_view.h"

#include "editor/views/soft_body_views/meshing/soft_body_meshing_settings_view.h"
#include "editor/views/soft_body_views/meshing/soft_body_meshing_creation_view.h"
#include "editor/views/soft_body_views/meshing/soft_body_meshing_info_view.h"

#include <gui/imgui/imgui.h>

#include <common/unique_ptr.h>

namespace ifx {

SoftBodyMeshingView::SoftBodyMeshingView(
    std::shared_ptr<ResourceManager> resource_manager){
    settings_view_ = ifx::make_unique<SoftBodyMeshingSettingsView>();
    creation_view_ = ifx::make_unique<SoftBodyMeshingCreationView>(resource_manager);
    info_view_ = ifx::make_unique<SoftBodyMeshingInfoView>();
}

bool SoftBodyMeshingView::Render(SoftBodyEditorObjects &soft_body_objects,
                                 SoftBodyRenderingEffects &rendering_effects){
    RenderSettings();
    bool is_mesh_created = RenderCreation(soft_body_objects,
                                       rendering_effects);
    RenderInfo();

    return is_mesh_created;
}

void SoftBodyMeshingView::RenderSettings(){
    settings_view_->Render();
}

bool SoftBodyMeshingView::RenderCreation(SoftBodyEditorObjects &soft_body_objects,
                                         SoftBodyRenderingEffects &rendering_effects){
    return creation_view_->Render(
        settings_view_->rtfem_options(),
        soft_body_objects,
        rendering_effects
    );
}

void SoftBodyMeshingView::RenderInfo(){
    info_view_->Render();
}

}