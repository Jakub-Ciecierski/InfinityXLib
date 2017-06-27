#include <gui/imgui/imgui.h>
#include "editor/views/main_menu.h"

#include <editor/views/scene_view.h>
#include <editor/views/physics_simulation_view.h>
#include <editor/views/imgui_demo_view.h>
#include <gui/theme.h>

namespace ifx{

MainMenu::MainMenu(
        std::shared_ptr<SceneView> scene_view,
        std::shared_ptr<PhysicsSimulationView> physics_simulation_view,
        std::shared_ptr<ImGuiDemoView> imgui_demo_view) :
    scene_view_(scene_view),
    physics_simulation_view_(physics_simulation_view),
    imgui_demo_view_(imgui_demo_view){}

MainMenu::~MainMenu(){}

void MainMenu::Render(){
    if (ImGui::BeginMainMenuBar()){
        RenderFile();
        RenderEdit();
        RenderView();
        RenderWindow();

        ImGui::EndMainMenuBar();
    }
}

void MainMenu::RenderFile(){
    if (ImGui::BeginMenu("File")){
        ImGui::EndMenu();
    }
}

void MainMenu::RenderEdit(){
    if (ImGui::BeginMenu("Edit")){

        ImGui::EndMenu();
    }
}

void MainMenu::RenderView(){
    if (ImGui::BeginMenu("View")){
        ImGui::MenuItem("Scene", NULL, scene_view_->show());
        ImGui::MenuItem("Physics", NULL, physics_simulation_view_->show());
        ImGui::MenuItem("ImGui Demo", NULL, imgui_demo_view_->show());

        static bool show_all = true;
        if(ImGui::MenuItem("All", NULL, &show_all)){
            scene_view_->show(show_all);
            physics_simulation_view_->show(show_all);
        }

        ImGui::EndMenu();
    }
}

void MainMenu::RenderWindow(){
    if (ImGui::BeginMenu("Window")){
        if (ImGui::BeginMenu("Style")){
            if(ImGui::MenuItem("Dracula")){
                GUIThemeDracula();
            }
            if(ImGui::MenuItem("ImGui Default")){
                GUIThemeIMGUIDefault();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
}


}



