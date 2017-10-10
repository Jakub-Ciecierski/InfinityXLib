#include "editor/views/soft_body_views/meshing/soft_body_meshing_settings_view.h"

#include <editor/views/soft_body_views/soft_body_structers.h>

#include <gui/imgui/imgui.h>

namespace ifx {

void SoftBodyMeshingSettingsView::Render() {
    if (ImGui::TreeNodeEx("Parameters",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::PushItemWidth(50);
        ImGui::SliderFloat("Maximum Volume",
                           &rtfem_options_.maximum_volume,
                           0, 10);
        ImGui::PopItemWidth();
        ImGui::TreePop();
    }
}

}