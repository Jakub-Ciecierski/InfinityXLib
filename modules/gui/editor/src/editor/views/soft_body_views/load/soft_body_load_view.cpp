#include "editor/views/soft_body_views/load/soft_body_load_view.h"

#include "editor/views/soft_body_views/soft_body_structers.h"

#include <game/components/physics/soft_body_fem_component.h>

#include <gui/imgui/imgui.h>

namespace ifx {

void SoftBodyLoadView::Render(SoftBodyEditorObjects& soft_body_objects){
    if(!CheckCorrectness(soft_body_objects))
        return;
    if (ImGui::TreeNodeEx("Body Force",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderBodyForce(soft_body_objects.soft_body_fem->fem_model());
        ImGui::TreePop();
    }
}

bool SoftBodyLoadView::CheckCorrectness(
    SoftBodyEditorObjects& soft_body_objects){
    if(!soft_body_objects.soft_body_fem){
        return false;
    }
    return true;
}

void SoftBodyLoadView::RenderBodyForce(rtfem::FEMModel<double>& fem_model){
    const auto& body_force = fem_model.body_force();
    float values[3] ={
        (float)body_force.x(),
        (float)body_force.y(),
        (float)body_force.z(),
    };

    ImGui::PushItemWidth(150);
    if(ImGui::InputFloat3("Body Force", values)){
        fem_model.SetBodyForce(Eigen::Vector3<double>(
            values[0], values[1], values[2]));
    }
    ImGui::PopItemWidth();
}

}