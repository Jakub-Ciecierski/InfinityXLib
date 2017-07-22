#include "editor/views/main_menu_view.h"

#include <editor/editor.h>
#include <editor/views/main_menu_items/main_menu_view_item.h>

#include <gui/imgui/imgui.h>
#include <gui/theme.h>

namespace ifx{

MainMenuView::MainMenuView() :
        View("Main Menu"),
        editor_(nullptr) {
    view_item_.reset(new MainMenuViewItem());
}

MainMenuView::~MainMenuView(){}

void MainMenuView::Render() {
    if (ImGui::BeginMainMenuBar()){
        FetchSize();

        RenderContent();

        ImGui::EndMainMenuBar();
    }
}

void MainMenuView::RegisterEditor(std::shared_ptr<Editor> editor){
    editor_ = editor;
}

void MainMenuView::RenderContent(){
    if(!editor_)
        return;
    RenderFile();
    RenderEdit();
    view_item_->Render(editor_);
    RenderWindow();
}

void MainMenuView::RenderFile(){
    if (ImGui::BeginMenu("File")){
        ImGui::EndMenu();
    }
}

void MainMenuView::RenderEdit(){
    if (ImGui::BeginMenu("Edit")){

        ImGui::EndMenu();
    }
}

void MainMenuView::RenderWindow(){
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



