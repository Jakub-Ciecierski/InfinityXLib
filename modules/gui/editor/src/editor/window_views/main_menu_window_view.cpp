#include "editor/window_views/main_menu_window_view.h"

#include <editor/editor.h>
#include <editor/window_views/main_menu_items/main_menu_view_item.h>
#include <editor/window_views/main_menu_items/main_menu_update_item.h>

#include <gui/imgui/imgui.h>
#include <gui/theme.h>

#include <game/architecture/engine_architecture.h>
#include <common/unique_ptr.h>

namespace ifx {

MainMenuWindowView::MainMenuWindowView(
    std::shared_ptr<EngineArchitecture> engine_architecture) :
    WindowView("Main Menu"),
    engine_architecture_(engine_architecture),
    editor_(nullptr) {
    view_item_ = ifx::make_unique<MainMenuViewItem>();
    update_item_ = ifx::make_unique<MainMenuUpdateItem>();
}

MainMenuWindowView::~MainMenuWindowView() {}

void MainMenuWindowView::Render() {
    if (ImGui::BeginMainMenuBar()) {
        FetchSize();

        RenderContent();

        ImGui::EndMainMenuBar();
    }
}

void MainMenuWindowView::RegisterEditor(std::shared_ptr<Editor> editor) {
    editor_ = editor;
}

void MainMenuWindowView::RenderContent() {
    if (!editor_)
        return;
    RenderFile();
    RenderEdit();
    view_item_->Render(editor_);
    RenderWindow();
}

void MainMenuWindowView::RenderFile() {
    if (ImGui::BeginMenu("File")) {
        ImGui::EndMenu();
    }
}

void MainMenuWindowView::RenderEdit() {
    if (ImGui::BeginMenu("Edit")) {
        update_item_->Render(*engine_architecture_);
        ImGui::EndMenu();
    }
}

void MainMenuWindowView::RenderWindow() {
    if (ImGui::BeginMenu("Window")) {
        if (ImGui::BeginMenu("Style")) {
            if (ImGui::MenuItem("Dracula")) {
                GUIThemeDracula();
            }
            if (ImGui::MenuItem("ImGui Default")) {
                GUIThemeIMGUIDefault();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
}

}



