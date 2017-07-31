#include "editor/window_view.h"

#include "editor/view.h"

#include <gui/imgui/imgui.h>

namespace ifx{

WindowView::WindowView(std::string name) :
        show_(true),
        name_(name),
        flags_(0) {}

WindowView::WindowView(std::vector<std::shared_ptr<View>> views,
                       std::string name) :
        show_(true),
        name_(name),
        flags_(0),
        views_(views) {}

WindowView::WindowView(std::shared_ptr<View> view,
                       std::string name) :
        show_(true),
        name_(name),
        flags_(0){
    views_.push_back(view);
}

WindowView::~WindowView(){}

void WindowView::Render(){
    if(!show_)
        return;

    ImGui::Begin(name_.c_str(), NULL, flags_);

    FetchSize();
    RenderContent();

    ImGui::End();
}

void WindowView::RenderContent(){
    for(auto& view : views_){
        if (ImGui::CollapsingHeader(view->name().c_str())) {
            view->Render();
        }
    }
}

void WindowView::FetchSize() {
    width_ = ImGui::GetWindowWidth();
    height_ = ImGui::GetWindowHeight();
}

void WindowView::SetFlags(ImGuiWindowFlags flags){
    flags_ = flags;
}

}