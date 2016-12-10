#include <gui/imgui/imgui.h>
#include "engine_gui/views/main_menu.h"

namespace ifx{

MainMenu::MainMenu(){}

MainMenu::~MainMenu(){}

void MainMenu::Render(){
    if (ImGui::BeginMainMenuBar()){
        if (ImGui::BeginMenu("File")){
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")){
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")){
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

}


