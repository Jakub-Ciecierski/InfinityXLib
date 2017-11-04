#include "editor/views/soft_body_views/material/soft_body_material_view.h"

#include <game/components/physics/soft_body_fem_component.h>

#include <gui/imgui/imgui.h>

namespace ifx {

void SoftBodyMaterialView::Render(
    rtfem::Material<double>& material){
    RenderMaterial(material);
}

void SoftBodyMaterialView::RenderMaterial(
    rtfem::Material<double>& material){
    float young_modulus = (float)material.young_modulus;
    float poisson_coefficient = (float)material.poisson_coefficient;
    float density = (float)material.density;
    float damping_mass = (float)material.damping_mass;
    float damping_stiffness = (float)material.damping_stiffness;

    ImGui::PushItemWidth(60);

    if(ImGui::InputFloat("Young Modulus",
                      &young_modulus,
                      0, 100000)){
        material.young_modulus = young_modulus;
    }

    if(ImGui::InputFloat("Poisson Coefficient",
                      &poisson_coefficient,
                      0, 0.5)){
        material.poisson_coefficient = poisson_coefficient;
    }

    if(ImGui::InputFloat("Density",
                      &density,
                      0, 1000)){
        material.density = density;
    }

    if(ImGui::InputFloat("Damping Mass",
                         &damping_mass,
                         0, 1000)){
        material.damping_mass = damping_mass;
    }

    if(ImGui::InputFloat("Damping Stiffness",
                         &damping_stiffness,
                         0, 1000)){
        material.damping_stiffness = damping_stiffness;
    }

    ImGui::PopItemWidth();
}

}