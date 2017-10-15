#include "editor/views/soft_body_views/picking/soft_body_node_selection.h"

#include <gui/imgui/imgui.h>

namespace ifx {

void SoftBodyNodeSelection::Reset(){
    selected_vertices_.clear();
}

void SoftBodyNodeSelection::NotifyIntersection(unsigned int index){
    ImGuiIO &io = ImGui::GetIO();
    if(io.KeyShift){
        if(IsSelected(index)){
            RemoveSelection(index);
        }else{
            AddSelection(index);
        }
    }else{
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

}