#include "editor/window_views/main_menu_items/main_menu_view_item.h"

#include <editor/editor.h>
#include <editor/window_view.h>
#include <editor/docker.h>

#include <gui/imgui/imgui.h>

namespace ifx {

MainMenuViewItem::MainMenuViewItem() {}

MainMenuViewItem::~MainMenuViewItem(){}

void MainMenuViewItem::Render(std::shared_ptr<Editor> editor){
    if (ImGui::BeginMenu("View")){
        RenderShowWindows(editor);
        RenderDocker(editor->docker());

        ImGui::EndMenu();
    }
}

void MainMenuViewItem::RenderShowWindows(std::shared_ptr<Editor> editor){
    if(ImGui::BeginMenu("Show")) {
        for (auto &view : editor->window_views()) {
            ImGui::MenuItem(view->name().c_str(), NULL, view->show());
        }

        ImGui::Separator();

        static bool show_all = true;
        if (ImGui::MenuItem("All", NULL, &show_all)) {
            for (auto &view : editor->window_views()) {
                view->show(show_all);
            }
        }

        ImGui::EndMenu();
    }
}

void MainMenuViewItem::RenderDocker(std::shared_ptr<Docker> docker){
    if(ImGui::Button("Docker Settings"))
        ImGui::OpenPopup("Docker Settings");
    if (ImGui::BeginPopupModal("Docker Settings", NULL,
                               ImGuiWindowFlags_AlwaysAutoResize)) {
        DockerSettings docker_settings = docker->docker_settings();

        RenderDockerHeader(docker, docker_settings);
        if(docker_settings.is_automatic_scale){
            RenderDockerAutomaticScale(docker_settings);
        }
        else{
            RenderDockerManualScale(docker_settings);
        }
        RenderDockerFooter();

        docker->docker_settings(docker_settings);

        ImGui::EndPopup();
    }
}

void MainMenuViewItem::RenderDockerHeader(std::shared_ptr<Docker> docker,
                                          DockerSettings& settings){
    static bool is_enabled = docker->IsEnabled();
    ImGui::Checkbox("Enable", &is_enabled);
    if(is_enabled)
        docker->Enable();
    else
        docker->Disable();

    ImGui::Separator();
    ImGui::Checkbox("Soft Body Window Full Screen",
                    &settings.soft_body_window_full);
    ImGui::Separator();
    ImGui::Checkbox("Automatic Scale", &settings.is_automatic_scale);
}

void MainMenuViewItem::RenderDockerAutomaticScale(
        DockerSettings& settings){
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    ImGui::SliderFloat("Automatic Scale",
                       &settings.automatic_scale,
                       0.1, 0.5);
    ImGui::PopItemWidth();
}

void MainMenuViewItem::RenderDockerManualScale(DockerSettings& settings){
    ImGui::Separator();
    ImGui::SliderFloat("Left Window Width",
                       &settings.left_view_width,
                       10, 1000);
    ImGui::SliderFloat("Right Window Width",
                       &settings.right_view_width,
                       10, 1000);
    ImGui::SliderFloat("Bottom Window Height",
                       &settings.bottom_view_height,
                       10, 1000);
}

void MainMenuViewItem::RenderDockerFooter(){
    ImGui::Separator();
    if (ImGui::Button("OK", ImVec2(120, 0))) {
        ImGui::CloseCurrentPopup();
    }
}

}