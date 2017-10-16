#include "editor/views/soft_body_views/material/soft_body_material_view.h"

#include <game/components/physics/soft_body_fem_component.h>

#include <gui/imgui/imgui.h>

namespace ifx {

void SoftBodyMaterialView::Render(
    std::shared_ptr<SoftBodyFEMComponent<double>> soft_body){
    if(!soft_body){
        ImGui::TextColored(ImVec4(255,0,0,255), "No Game Object Selected");
        return;
    }
    RenderMaterial(soft_body);
}

void SoftBodyMaterialView::RenderMaterial(
    std::shared_ptr<SoftBodyFEMComponent<double>> soft_body){
    auto material = soft_body->fem_model().material();

    float young_modulus = (float)material.young_modulus;
    float poisson_coefficient = (float)material.poisson_coefficient;
    float density = (float)material.density;

    bool value_changed = false;

    ImGui::PushItemWidth(60);

    if(ImGui::InputFloat("Young Modulus",
                      &young_modulus,
                      0, 100000)){
        material.young_modulus = young_modulus;
        value_changed = true;
    }

    if(ImGui::InputFloat("Poisson Coefficient",
                      &poisson_coefficient,
                      0, 0.5)){
        material.poisson_coefficient = poisson_coefficient;
        value_changed = true;
    }

    if(ImGui::InputFloat("Density",
                      &density,
                      0, 1000)){
        material.density = density;
        value_changed = true;
    }
    ImGui::PopItemWidth();

    if(value_changed){
        soft_body->fem_model().material(material);
    }
}

}