#include "editor/views/soft_body_views/load/soft_body_load_view.h"

#include "editor/views/soft_body_views/soft_body_structers.h"
#include <editor/views/soft_body_views/picking/soft_body_picker.h>
#include <editor/views/soft_body_views/picking/soft_body_node_selection.h>
#include <editor/views/soft_body_views/load/traction_force_recorder.h>

#include <game/components/render/render_component.h>
#include <game/components/physics/soft_body_fem_component.h>

#include <gui/imgui/imgui.h>

#include <common/unique_ptr.h>
#include <iostream>

namespace ifx {

SoftBodyLoadView::SoftBodyLoadView(
    std::shared_ptr<RenderComponent> traction_force,
    std::shared_ptr<SoftBodyPicker> soft_body_picker) :
    traction_force_(traction_force),
    soft_body_picker_(soft_body_picker),
    is_recording_traction_force_(false),
    selected_triangle_face_(-1){
    traction_force_recorder_
        = ifx::make_unique<TractionForceRecorder>(traction_force);
}

void SoftBodyLoadView::Render(
    Eigen::Vector3<double>& body_force,
    std::vector<rtfem::TriangleFace<double>>& triangle_faces){
    if (ImGui::TreeNodeEx("Body Force",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderBodyForce(body_force);
        ImGui::TreePop();
    }
    if (ImGui::TreeNodeEx("Traction Forces",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        if(RenderTractionForceError(triangle_faces)){
            RenderTractionForce(triangle_faces);
        }
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

void SoftBodyLoadView::RenderTractionForce(
    std::vector<rtfem::TriangleFace<double>>& triangle_faces){
    RenderTractionForceIsRecording();
    RenderTractionForceInspector(triangle_faces);
    RenderTractionForceCurrent(triangle_faces);
    RecordTractionForce(triangle_faces);
}

void SoftBodyLoadView::RenderTractionForceIsRecording(){
    std::string display;
    if(is_recording_traction_force_){
        display = "Stop Adding Traction Forces";
    }else{
        display = "Start Adding Traction Forces";
    }

    ImGui::Checkbox(display.c_str(),
                    &is_recording_traction_force_);
}

void SoftBodyLoadView::RenderTractionForceCurrent(
    std::vector<rtfem::TriangleFace<double>>& triangle_faces){
    ImGui::BeginChild(ImGui::GetID((void *) (intptr_t) 0),
                      ImVec2(ImGui::GetWindowWidth() * 0.17f,
                             ImGui::GetWindowHeight() * 0.3f),
                      false);
    static int selection_mask = (1 << 2);
    for (unsigned int i = 0; i < triangle_faces.size(); i++) {
        if(triangle_faces[i].traction_force == 0)
            continue;
        auto name = std::to_string(i);
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
            selected_triangle_face_ = i;
        }

        if (node_open) {
            ImGui::TreePop();
        }
    }

    ImGui::EndChild();
}

void SoftBodyLoadView::RenderTractionForceInspector(
    std::vector<rtfem::TriangleFace<double>>& triangle_faces){
    if (ImGui::TreeNodeEx("Inspector",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        if(selected_triangle_face_ >= 0){
            auto& triangle_face = triangle_faces[selected_triangle_face_];
            float imgui_traction_force = (float)triangle_face.traction_force;

            ImGui::PushItemWidth(50);
            if(ImGui::InputFloat("Traction Force", &imgui_traction_force)){
                triangle_face.traction_force = imgui_traction_force;
            }
            ImGui::PopItemWidth();
        }

        ImGui::TreePop();
    }
}

void SoftBodyLoadView::RecordTractionForce(
    std::vector<rtfem::TriangleFace<double>>& triangle_faces){
    if(is_recording_traction_force_){
        soft_body_picker_->DisableBoxCasting();

        const auto& face_selection = soft_body_picker_->face_selection();
        if(ImGui::IsMouseClicked(0)){
            traction_force_recorder_->Begin(
                soft_body_picker_->last_mouse_position()
            );
        }
        if(ImGui::IsMouseReleased(0)){
            traction_force_recorder_->End();

            auto selected_indices = face_selection.selected_vertices();
            for(auto selected_index : selected_indices){
                triangle_faces[selected_index].traction_force =
                    traction_force_recorder_->GetMagnitude();
            }
        }
        traction_force_recorder_->Update(
            soft_body_picker_->window_width(),
            soft_body_picker_->window_height(),
            soft_body_picker_->last_mouse_position());
    }else{
        soft_body_picker_->EnableBoxCasting();
    }
}

bool SoftBodyLoadView::RenderTractionForceError(
    const std::vector<rtfem::TriangleFace<double>>& triangle_faces){
    bool is_success = true;
    if(triangle_faces.size() == 0){
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255, 0, 0, 255));
        ImGui::Bullet();
        ImGui::SameLine();
        ImGui::TextWrapped("Error: No triangle faces exist");
        ImGui::PopStyleColor();
        is_success = false;
    }
    return is_success;
}

}