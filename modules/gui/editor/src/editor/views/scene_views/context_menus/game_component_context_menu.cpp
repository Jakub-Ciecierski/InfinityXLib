#include "editor/views/scene_views/context_menus/game_component_context_menu.h"

#include <game/game_object.h>

#include <gui/imgui/imgui.h>

namespace ifx {

GameComponentContextMenu::GameComponentContextMenu() {}

GameComponentContextMenu::~GameComponentContextMenu() {}

GameComponentContextMenuEvent
GameComponentContextMenu::Render(std::shared_ptr<GameObject> game_object,
                                 std::shared_ptr<GameComponent> component,
                                 int component_id) {
    GameComponentContextMenuEvent event = GameComponentContextMenuEvent::None;
    ImGui::PushID(std::to_string(component_id).c_str());
    if (ImGui::BeginPopupContextItem("GameComponent context menu")) {
        if (ImGui::Selectable("Remove")) {
            Remove(game_object, component);
            event = GameComponentContextMenuEvent::Remove;
        }
        ImGui::EndPopup();
    }
    ImGui::PopID();

    return event;
}

void GameComponentContextMenu::Remove(std::shared_ptr<GameObject> game_object,
                                      std::shared_ptr<GameComponent> component) {
    game_object->Remove(component);
}

}