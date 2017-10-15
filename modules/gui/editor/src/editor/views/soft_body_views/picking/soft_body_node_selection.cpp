#include "editor/views/soft_body_views/picking/soft_body_node_selection.h"

#include <gui/imgui/imgui.h>

namespace ifx {

void SoftBodyNodeSelection::Reset(){
    selected_vertices_.clear();
}

void SoftBodyNodeSelection::NotifyIntersection(
    unsigned int index, SelectionType type){
    if(IsInputShiftModifier()){
        if(IsSelected(index)){
            RemoveSelection(index);
        }else{
            AddSelection(index);
        }
    }else{
        if(type == SelectionType::Ray)
            Reset();
        AddSelection(index);
    }
}

bool SoftBodyNodeSelection::IsSelected(unsigned int index){
    for(unsigned int i = 0;i < selected_vertices_.size(); i++){
        if(selected_vertices_[i] == index)
            return true;
    }
    return false;
}

void SoftBodyNodeSelection::AddSelection(unsigned int selected){
    selected_vertices_.push_back(selected);
}

bool SoftBodyNodeSelection::RemoveSelection(unsigned int selected){
    for (unsigned int i = 0; i < selected_vertices_.size(); i++) {
        if (selected_vertices_[i] == selected) {
            selected_vertices_.erase(selected_vertices_.begin() + i);
            return true;
        }
    }
    return false;
}

bool SoftBodyNodeSelection::IsInputBeginBoxCasting(){
    return ImGui::IsMouseClicked(0);
}

bool SoftBodyNodeSelection::IsInputUpdateBoxCasting(){
    ImGuiIO &io = ImGui::GetIO();
    return (io.MouseDownDuration[0] >= 0.0f);
}

bool SoftBodyNodeSelection::IsInputEndBoxCasting(){
    return ImGui::IsMouseReleased(0);
}

bool SoftBodyNodeSelection::IsInputRayCasting(){
    return ImGui::IsMouseClicked(0);
}

bool SoftBodyNodeSelection::IsInputShiftModifier(){
    ImGuiIO &io = ImGui::GetIO();
    return io.KeyShift;
}

}