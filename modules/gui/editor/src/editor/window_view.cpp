#include "editor/window_view.h"

#include "editor/view.h"

#include <gui/imgui/imgui.h>

namespace ifx{

WindowView::WindowView(std::string name) :
        show_(true),
        is_focused_(false),
        name_(name),
        flags_(0),
        selected_view_(nullptr){}

WindowView::WindowView(std::vector<std::shared_ptr<View>> views,
                       std::string name) :
        show_(true),
        is_focused_(false),
        name_(name),
        flags_(0),
        selected_view_(nullptr),
        views_(views){
    for(unsigned int i = 0; i < views.size(); i++){
        selected_views_.push_back(0);
    }
    selected_views_[0] = 1;
}

WindowView::WindowView(std::shared_ptr<View> view,
                       std::string name) :
        show_(true),
        is_focused_(false),
        name_(name),
        flags_(0),
        selected_view_(nullptr){
    views_.push_back(view);

    selected_views_.push_back(1);
}

bool WindowView::Terminate(){
    for(auto& view : views_){
        if(!view->Terminate())
            return false;
    }
    return true;
}

void WindowView::Render(){
    if(!show_)
        return;

    ImGuiStyle& style = ImGui::GetStyle();
    auto old_color = style.Colors[ImGuiCol_Border];
    if(is_focused_){
        style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.40f, 0.57f, 1.00f);
    }

    ImGui::Begin(name_.c_str(), NULL, flags_);
    FetchWindowInfo();
    RenderContent();
    ImGui::End();

    style.Colors[ImGuiCol_Border] = old_color;
}

void WindowView::RenderContent(){
    RenderViewTabs();
    ImGui::Separator();
    RenderSelectedView();
}

void WindowView::RenderViewTabs(){
    for(unsigned int i = 0; i < views_.size(); i++){
        bool selected = selected_views_[i] == 1;

        if (ImGui::Selectable(views_[i]->name().c_str(), &selected,
                              0, ImVec2(75,17))) {
            for(unsigned int j = 0; j < views_.size(); j++){
                if(i != j)
                    selected_views_[j] = 0;
            }
            selected_views_[i] = 1;
        }

        if(i != views_.size()-1)
            ImGui::SameLine();
    }
}

void WindowView::RenderSelectedView(){
    if(views_.size() == 0)
        return;
    unsigned int view_to_render = 0;
    for(unsigned int i = 0; i < views_.size(); i++){
        if(selected_views_[i] == 1)
            view_to_render = i;
    }
    selected_view_ = views_[view_to_render];
    selected_view_->Render();
}

void WindowView::SetFlags(ImGuiWindowFlags flags){
    flags_ = flags;
}

void WindowView::FetchWindowInfo(){
    FetchSize();
    FetchFocus();
}

void WindowView::FetchSize() {
    width_ = ImGui::GetWindowWidth();
    height_ = ImGui::GetWindowHeight();
}

void WindowView::FetchFocus(){
    is_focused_ = ImGui::IsWindowFocused();

    for(auto& view : views_){
        view->is_window_focused(false);
    }

    if(selected_view_)
        selected_view_->is_window_focused(is_focused_);
}

}