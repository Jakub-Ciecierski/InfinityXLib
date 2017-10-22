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
    is_recording_traction_force_(false){
    traction_force_recorder_
        = ifx::make_unique<TractionForceRecorder>(traction_force);
}

void SoftBodyLoadView::Render(Eigen::Vector3<double>& body_force){
    if (ImGui::TreeNodeEx("Body Force",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderBodyForce(body_force);
        ImGui::TreePop();
    }
    if (ImGui::TreeNodeEx("Traction Forces",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderTractionForce();
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

void SoftBodyLoadView::RenderTractionForce(){
    RenderTractionForceIsRecording();
    RenderTractionForceCurrent();

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
            traction_force_recorder_->GetMagnitude();
        }
        traction_force_recorder_->Update(
            soft_body_picker_->window_width(),
            soft_body_picker_->window_height(),
            soft_body_picker_->last_mouse_position());
    }else{
        soft_body_picker_->EnableBoxCasting();
    }
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

void SoftBodyLoadView::RenderTractionForceCurrent(){

}

}