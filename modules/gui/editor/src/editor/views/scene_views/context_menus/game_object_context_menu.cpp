#include "editor/views/scene_views/context_menus/game_object_context_menu.h"

#include "editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object.h"
#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_light.h>

#include <game/game_object.h>
#include <game/scene_container.h>
#include <game/resources/resource_context.h>

#include <gui/imgui/imgui.h>

namespace ifx {

GameObjectContextMenu::GameObjectContextMenu(
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<ResourceContext> resource_creator,
        std::shared_ptr<SceneContainer> scene) :
        scene_renderer_(scene_renderer),
        resource_creator_(resource_creator),
        scene_(scene) {
    context_menu_add_light_.reset(new ContextMenuAddLight());
    context_menu_add_render_object_.reset(new ContextMenuAddRenderObject());
}

GameObjectContextMenu::~GameObjectContextMenu(){}

void GameObjectContextMenu::Render(std::shared_ptr<GameObject> game_object,
                                   int game_object_id) {
    ImGui::PushID(std::to_string(game_object_id).c_str());
    if (ImGui::BeginPopupContextItem("GameObject context menu")) {

        Add(scene_renderer_, resource_creator_, game_object);
        ImGui::Separator();
        Remove(scene_, game_object);

        ImGui::EndPopup();
    }
    ImGui::PopID();
}

void GameObjectContextMenu::Remove(std::shared_ptr<SceneContainer> scene,
                                   std::shared_ptr<GameObject> game_object) {
    if (ImGui::Selectable("Remove")) {
        scene->Remove(game_object);
    }
}

void GameObjectContextMenu::Add(std::shared_ptr<SceneRenderer> scene_renderer,
                                std::shared_ptr<ResourceContext> resource_creator,
                                std::shared_ptr<GameObject> game_object) {
    if (ImGui::BeginMenu("Add")) {
        AddLight(resource_creator, game_object);
        AddRenderObject(scene_renderer, resource_creator, game_object);
        ImGui::EndMenu();
    }
}

void GameObjectContextMenu::AddLight(std::shared_ptr<ResourceContext> resource_creator,
                                     std::shared_ptr<GameObject> game_object) {
    context_menu_add_light_->Render(resource_creator, game_object);
}

void GameObjectContextMenu::AddRenderObject(
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<ResourceContext> resource_creator,
        std::shared_ptr<GameObject> game_object) {
    context_menu_add_render_object_->Render(
            scene_renderer,resource_creator, game_object);
}

}

