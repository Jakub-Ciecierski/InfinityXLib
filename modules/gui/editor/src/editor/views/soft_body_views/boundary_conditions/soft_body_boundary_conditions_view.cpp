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
    SoftBodyEditorObjects& soft_body_objects){
    if(!StaticCorrectnessAndThrowException(soft_body_objects)){
        selected_boundary_condition_ = nullptr;
        return;
    }
    if(!CheckDynamicCorrectness(soft_body_objects)){
        selected_boundary_condition_ = nullptr;
        return;
    }

    if (ImGui::TreeNodeEx("Current Boundary Conditions",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderCurrentBoundaryConditionsContextMenu(
            soft_body_objects.soft_body_fem->fem_model());

        ImGui::BeginChild(ImGui::GetID((void *) (intptr_t) 0),
                          ImVec2(ImGui::GetWindowWidth() * 0.17f,
                                 ImGui::GetWindowHeight() * 0.3f),
                          false);
        RenderCurrentBoundaryConditions(
            soft_body_objects.soft_body_fem->fem_model());
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
        RenderNewBoundaryConditions(
            soft_body_objects.soft_body_fem->fem_model());
        ImGui::TreePop();
    }
}

bool SoftBodyBoundaryConditionsView::StaticCorrectnessAndThrowException(
    const SoftBodyEditorObjects& soft_body_objects){
    if(picker_->current_picked() != soft_body_objects.soft_body_fem_render){
        return false;
    }
    return true;
}

bool SoftBodyBoundaryConditionsView::CheckDynamicCorrectness(
    const SoftBodyEditorObjects& soft_body_objects){
    if(!soft_body_objects.soft_body_fem)
        return false;
    return true;
}

void
SoftBodyBoundaryConditionsView::RenderCurrentBoundaryConditionsContextMenu(
    rtfem::FEMModel<double>& fem_model){
    if (ImGui::BeginPopupContextItem("Current BC Context Menu")) {
        if (ImGui::Selectable("Clear")) {
            auto& boundary_conditions = fem_model.boundary_conditions();
            boundary_conditions.Clear();

            selected_boundary_condition_ = nullptr;
        }
        ImGui::EndPopup();
    }
}

void SoftBodyBoundaryConditionsView::RenderCurrentBoundaryConditions(
    rtfem::FEMModel<double>& fem_model){
    const auto& boundary_conditions = fem_model.boundary_conditions();
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
                                                       i,
                                                       fem_model)){
            boundary_conditions_to_remove.push_back(boundary_conditions[i]);
        }

        if (node_open) {
            ImGui::TreePop();
        }
    }

    for(const auto& boundary_condition : boundary_conditions_to_remove){
        fem_model.boundary_conditions().
            RemoveBoundaryCondition(boundary_condition);
    }
}

bool
SoftBodyBoundaryConditionsView::RenderSelectedBoundaryConditionsContextMenu(
    const rtfem::BoundaryCondition<double>& boundary_condition,
    int id,
    rtfem::FEMModel<double>& fem_model){
    bool has_removed = false;
    ImGui::PushID(std::to_string(id).c_str());
    if (ImGui::BeginPopupContextItem("Selected BC Context Menu")) {
        if (ImGui::Selectable("Remove")) {
            selected_boundary_condition_ = nullptr;
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
    rtfem::FEMModel<double>& fem_model){
    static float values[3] = {0, 0, 0};

    ImGui::PushItemWidth(150);
    ImGui::InputFloat3("New BC", values);
    ImGui::PopItemWidth();

    if(ImGui::Button("Add")){
        const auto& selected_nodes =
            picker_->node_selection().selected_vertices();
        for(auto selected_node : selected_nodes){
            const auto& vertex
                = fem_model.fem_geometry().vertices[selected_node];

            auto value = Eigen::Vector3<double>(
                values[0], values[1], values[2]);
            auto new_boundary_condition = rtfem::BoundaryCondition<double>{
                vertex->id(), value};
            fem_model.boundary_conditions().
                AddBoundaryCondition(new_boundary_condition);

            selected_boundary_condition_ = nullptr;
        }
    }
}

}