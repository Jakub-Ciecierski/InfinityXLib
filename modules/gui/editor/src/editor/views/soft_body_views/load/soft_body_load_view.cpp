#include "editor/views/soft_body_views/load/soft_body_load_view.h"

#include "editor/views/soft_body_views/soft_body_structers.h"

#include <game/components/physics/soft_body_fem_component.h>

#include <gui/imgui/imgui.h>

namespace ifx {

void SoftBodyLoadView::Render(Eigen::Vector3<double>& body_force){
    if (ImGui::TreeNodeEx("Body Force",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderBodyForce(body_force);
        ImGui::TreePop();
    }
}

void SoftBodyLoadView::RenderBodyForce(
    Eigen::Vector3<double>& body_force){
    float values[3] ={
        (float)body_force.x(),
        (float)body_force.y(),
        (float)body_force.z(),
    };

    ImGui::PushItemWidth(150);
    if(ImGui::InputFloat3("Body Force", values)){
        body_force[0] = values[0];
        body_force[1] = values[1];
        body_force[2] = values[2];
    }
    ImGui::PopItemWidth();
}

}