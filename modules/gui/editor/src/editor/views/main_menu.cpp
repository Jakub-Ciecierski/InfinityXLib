#include "editor/views/main_menu.h"

#include <editor/editor.h>
#include <editor/views/main_menu_items/main_menu_view_item.h>

#include <gui/imgui/imgui.h>
#include <gui/theme.h>

namespace ifx{

MainMenu::MainMenu() :
        View("Main Menu"),
        editor_(nullptr) {
    view_item_.reset(new MainMenuViewItem());
}

MainMenu::~MainMenu(){}

void MainMenu::Render() {
    if (ImGui::BeginMainMenuBar()){
        FetchSize();

        RenderContent();

        ImGui::EndMainMenuBar();
    }
}

void MainMenu::RegisterEditor(std::shared_ptr<Editor> editor){
    editor_ = editor;
}

void MainMenu::RenderContent(){
    if(!editor_)
        return;
    RenderFile();
    RenderEdit();
    view_item_->Render(editor_);
    RenderWindow();
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



