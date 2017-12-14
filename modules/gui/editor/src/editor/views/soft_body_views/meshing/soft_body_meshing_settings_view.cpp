#include "editor/views/soft_body_views/meshing/soft_body_meshing_settings_view.h"

#include <editor/views/soft_body_views/soft_body_structers.h>

#include <gui/imgui/imgui.h>

namespace ifx {

void SoftBodyMeshingSettingsView::Render() {
    if (ImGui::TreeNodeEx("Parameters",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::PushItemWidth(50);
        ImGui::InputFloat("Max Volume",
                          &rtfem_options_.maximum_volume);
        ImGui::InputFloat("Max Radius-Edge Ratio",
                          &rtfem_options_.max_radius_edge_ratio);
        ImGui::PopItemWidth();

        ImGui::PushItemWidth(100);
        ImGui::InputInt("Min Dihedral Angle",
                        &rtfem_options_.min_dihedral_angle_degree);
        ImGui::PopItemWidth();

        ImGui::TreePop();
    }
}

}