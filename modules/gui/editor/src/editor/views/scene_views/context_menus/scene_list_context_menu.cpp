#include "editor/views/scene_views/context_menus/scene_list_context_menu.h"

#include <game/scene_container.h>

#include <gui/imgui/imgui.h>

namespace ifx {

SceneListContextMenu::SceneListContextMenu(std::shared_ptr<SceneContainer> scene)
    :
    scene_(scene) {}

SceneListContextMenu::~SceneListContextMenu() {}

void SceneListContextMenu::Render() {
    if (ImGui::BeginPopupContextItem("GameObjects context menu")) {
        if (ImGui::Selectable("New Game Object")) {
            scene_->CreateAndAddEmptyGameObject();
        }
        ImGui::EndPopup();
    }
}

}