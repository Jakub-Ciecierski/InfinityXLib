#include "editor/view.h"

#include <gui/imgui/imgui.h>

namespace ifx{

View::View(std::string name) :
        show_(true),
        name_(name),
        flags_(0) {}
View::~View(){}

void View::Render(){
    if(!show_)
        return;

    ImGui::Begin(name_.c_str(), NULL, flags_);

    FetchSize();
    RenderContent();

    ImGui::End();
}

void View::FetchSize() {
    width_ = ImGui::GetWindowWidth();
    height_ = ImGui::GetWindowHeight();
}

void View::SetFlags(ImGuiWindowFlags flags){
    flags_ = flags;
}

}