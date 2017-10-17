#include <editor/views/soft_body_views/soft_body_structers.h>
#include "editor/views/soft_body_views/boundary_conditions/soft_body_boundary_conditions_view.h"

#include "editor/views/soft_body_views/picking/soft_body_picker.h"
#include "editor/views/soft_body_views/picking/soft_body_node_selection.h"

#include <game/components/physics/soft_body_fem_component.h>

#include <gui/imgui/imgui.h>

#include <RTFEM/FEM/FEMGeometry.h>
#include <RTFEM/FEM/BoundaryConditionContainer.h>
#include <RTFEM/FEM/BoundaryCondition.h>
#include <RTFEM/FEM/Vertex.h>

#include <iostream>

namespace ifx {

SoftBodyBoundaryConditionsView::SoftBodyBoundaryConditionsView(
    std::shared_ptr<SoftBodyPicker> picker) :
    picker_(picker),
    selected_boundary_condition_(nullptr){}

void SoftBodyBoundaryConditionsView::Render(
    rtfem::BoundaryConditionContainer<double>& boundary_conditions,
    rtfem::FEMGeometry<double>& fem_geometry){
    if (ImGui::TreeNodeEx("Current Boundary Conditions",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderCurrentBoundaryConditionsContextMenu(boundary_conditions);

        ImGui::BeginChild(ImGui::GetID((void *) (intptr_t) 0),
                          ImVec2(ImGui::GetWindowWidth() * 0.17f,
                                 ImGui::GetWindowHeight() * 0.3f),
                          false);
        RenderCurrentBoundaryConditions(boundary_conditions);
        ImGui::EndChild();
        ImGui::TreePop();
    }

    if (ImGui::TreeNodeEx("Inspector",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderSelectedBoundaryCondition();
        ImGui::TreePop();
    }

    if (ImGui::TreeNodeEx("New Boundary Conditions",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderNewBoundaryConditions(boundary_conditions,
                                    fem_geometry);
        ImGui::TreePop();
    }
}

void
SoftBodyBoundaryConditionsView::RenderCurrentBoundaryConditionsContextMenu(
    rtfem::BoundaryConditionContainer<double>& boundary_conditions){
    if (ImGui::BeginPopupContextItem("Current BC Context Menu")) {
        if (ImGui::Selectable("Clear")) {
            boundary_conditions.Clear();

            ResetSelectedBoundaryCondition();
        }
        ImGui::EndPopup();
    }
}

void SoftBodyBoundaryConditionsView::RenderCurrentBoundaryConditions(
    rtfem::BoundaryConditionContainer<double>& boundary_conditions){
    std::vector<rtfem::BoundaryCondition<double>> boundary_conditions_to_remove;

    static int selection_mask = (1 << 2);
    for (unsigned int i = 0; i < boundary_conditions.Size(); i++) {
        auto name = std::to_string(boundary_conditions[i].vertex_id);
        int node_clicked = -1;
        ImGuiTreeNodeFlags node_flags
            = ImGuiTreeNodeFlags_Bullet | ((selection_mask & (1 << i)) ?
                                           ImGuiTreeNodeFlags_Selected : 0);
        bool node_open = ImGui::TreeNodeEx((void *) (intptr_t) i,
                                           node_flags, name.c_str(), i);

        if (ImGui::IsItemClicked()) {
            node_clicked = i;
        }

        if (node_clicked != -1) {
            selection_mask = (1 << node_clicked);
            selected_boundary_condition_ = &(boundary_conditions[i]);
        }
        if(RenderSelectedBoundaryConditionsContextMenu(boundary_conditions[i],
                                                       i)){
            boundary_conditions_to_remove.push_back(boundary_conditions[i]);
        }

        if (node_open) {
            ImGui::TreePop();
        }
    }

    for(const auto& boundary_condition : boundary_conditions_to_remove){
        boundary_conditions.RemoveBoundaryCondition(boundary_condition);
    }
}

bool
SoftBodyBoundaryConditionsView::RenderSelectedBoundaryConditionsContextMenu(
    const rtfem::BoundaryCondition<double>& boundary_condition,
    int id){
    bool has_removed = false;
    ImGui::PushID(std::to_string(id).c_str());
    if (ImGui::BeginPopupContextItem("Selected BC Context Menu")) {
        if (ImGui::Selectable("Remove")) {
            ResetSelectedBoundaryCondition();
            has_removed = true;
        }
        ImGui::EndPopup();
    }
    ImGui::PopID();

    return has_removed;
}

void SoftBodyBoundaryConditionsView::RenderSelectedBoundaryCondition(){
    if(!selected_boundary_condition_)
        return;
    const auto& value = selected_boundary_condition_->value;
    float values[3] = {(float)value.x(),
                       (float)value.y(),
                       (float)value.z()};
    ImGui::PushItemWidth(150);
    ImGui::InputFloat3("BC", values);
    ImGui::PopItemWidth();
}

void SoftBodyBoundaryConditionsView::RenderNewBoundaryConditions(
    rtfem::BoundaryConditionContainer<double>& boundary_conditions,
    rtfem::FEMGeometry<double>& fem_geometry){
    static float values[3] = {0, 0, 0};

    ImGui::PushItemWidth(150);
    ImGui::InputFloat3("New BC", values);
    ImGui::PopItemWidth();

    if(ImGui::Button("Add")){
        const auto& selected_nodes =
            picker_->node_selection().selected_vertices();
        for(auto selected_node : selected_nodes){
            const auto& vertex
                = fem_geometry.vertices[selected_node];

            auto value = Eigen::Vector3<double>(
                values[0], values[1], values[2]);
            auto new_boundary_condition = rtfem::BoundaryCondition<double>{
                vertex->id(), value};
            boundary_conditions.
                AddBoundaryCondition(new_boundary_condition);

            ResetSelectedBoundaryCondition();
        }
    }

}
void SoftBodyBoundaryConditionsView::ResetSelectedBoundaryCondition() {
    selected_boundary_condition_ = nullptr;
}

}