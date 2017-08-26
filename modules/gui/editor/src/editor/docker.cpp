#include "editor/docker.h"

#include <editor/window_view.h>
#include <graphics/rendering/window/window.h>

#include <gui/imgui/imgui.h>

namespace ifx {

Docker::Docker(std::shared_ptr<Window> window) :
        window_(window),
        left_window_view_(nullptr),
        right_window_view_(nullptr),
        top_window_view_(nullptr),
        bottom_window_view_(nullptr),
        is_enabled_(true),
        docker_settings_{250, 250, 250, true, 0.2, false}{}

Docker::~Docker(){}

void Docker::Enable(){
    is_enabled_ = true;
    SetEnabledFlags();
}

void Docker::Disable(){
    is_enabled_ = false;
    SetDisabledFlags();
}

void Docker::RegisterView(std::shared_ptr<WindowView> view,
                          const DockPosition &dock_position) {
    switch(dock_position){
        case DockPosition::Left:
            left_window_view_ = view;
            break;
        case DockPosition::Right:
            right_window_view_ = view;
            break;
        case DockPosition::Top:
            top_window_view_ = view;
            break;
        case DockPosition::Bottom:
            bottom_window_view_ = view;
            break;
        case DockPosition::SoftBody:
            soft_body_window_view_ = view;
            break;
    }

    if(!is_enabled_){
        SetDisabledFlags();
    }else{
        SetEnabledFlags();
    }
}

void Docker::SetDisabledFlags(){
    SetFlags(0);
}

void Docker::SetEnabledFlags(){
    SetFlags(ImGuiWindowFlags_NoResize
             | ImGuiWindowFlags_NoTitleBar
             | ImGuiWindowFlags_NoMove
             | ImGuiWindowFlags_NoCollapse
             | ImGuiWindowFlags_ShowBorders
             | ImGuiWindowFlags_HorizontalScrollbar);
}

void Docker::SetFlags(ImGuiWindowFlags flags){
    if(left_window_view_)
        left_window_view_->SetFlags(flags);
    if(right_window_view_)
        right_window_view_->SetFlags(flags);
    if(top_window_view_)
        top_window_view_->SetFlags(flags);
    if(bottom_window_view_)
        bottom_window_view_->SetFlags(flags);
    if(soft_body_window_view_)
        soft_body_window_view_->SetFlags(flags);
}

void Docker::Dock(std::shared_ptr<WindowView> view){
    if(!is_enabled_)
        return;

    UpdateAutomaticSize();

    if(view == left_window_view_){
        DockLeft();
    }
    else if(view == right_window_view_){
        DockRight();
    }
    else if(view == top_window_view_){
        DockTop();
    }
    else if(view == bottom_window_view_){
        DockBottom();
    }
    else if(view == soft_body_window_view_){
        DockSoftBodyWindow();
    }

}

void Docker::UpdateAutomaticSize(){
    if(!docker_settings_.is_automatic_scale)
        return;

    float width = *window_->width() * docker_settings_.automatic_scale;
    float height = *window_->height() * docker_settings_.automatic_scale;

    docker_settings_.left_view_width = width;
    docker_settings_.right_view_width = width;
    docker_settings_.bottom_view_height = height;
}

void Docker::DockLeft(){
    float top_view_height = top_window_view_->height();

    float view_width = docker_settings_.left_view_width;
    float view_height = *(window_->height()) - top_view_height;

    ImGui::SetNextWindowPos(ImVec2(0, top_view_height));
    ImGui::SetNextWindowSize(ImVec2(view_width, view_height));
}

void Docker::DockRight(){
    float top_view_height = top_window_view_->height();

    float view_width = docker_settings_.right_view_width;
    float view_height = *(window_->height()) - top_view_height;

    float view_pos_x = *(window_->width()) - view_width;

    ImGui::SetNextWindowPos(ImVec2(view_pos_x, top_view_height));
    ImGui::SetNextWindowSize(ImVec2(view_width, view_height));
}

void Docker::DockTop(){
    // Assume main menu resizes it self
}

void Docker::DockBottom(){
    float left_view_width = left_window_view_->width();
    float right_view_width = right_window_view_->width();

    const float epsilon_gap_closer = 1.0f;
    float view_width = *(window_->width()) - left_view_width - right_view_width
                       + epsilon_gap_closer;
    float view_height = docker_settings_.bottom_view_height;

    float view_pos_x = left_view_width;
    float view_pos_y = *(window_->height()) - view_height;

    ImGui::SetNextWindowPos(ImVec2(view_pos_x, view_pos_y));
    ImGui::SetNextWindowSize(ImVec2(view_width, view_height + epsilon_gap_closer));
}

void Docker::DockSoftBodyWindow(){
    float pos_x, pos_y, view_width, view_height;

    if(docker_settings_.soft_body_window_full){
        pos_x = 0;
        pos_y = top_window_view_->height();

        view_width = *(window_->width());
        view_height = *(window_->height()) - pos_y;
    }else{
        pos_x = left_window_view_->width();
        pos_y = top_window_view_->height();

        const float epsilon_gap_closer = 1.0f;
        view_width = *(window_->width()) -
                           right_window_view_->width() -
                           left_window_view_->width();
        view_height = *(window_->height()) -
                      pos_y -
                      bottom_window_view_->height() +
                      epsilon_gap_closer;
    }

    ImGui::SetNextWindowPos(ImVec2(pos_x, pos_y));
    ImGui::SetNextWindowSize(ImVec2(view_width, view_height));
}

}