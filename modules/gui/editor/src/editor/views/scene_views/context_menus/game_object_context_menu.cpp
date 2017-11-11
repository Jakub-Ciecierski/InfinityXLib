#include "editor/views/scene_views/context_menus/game_object_context_menu.h"

#include "editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object.h"
#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_light.h>
#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_rigid_body.h>

#include <game/game_object.h>
#include <game/scene_container.h>
#include <game/resources/resource_context.h>

#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object/context_menu_add_render_object_parametric_equation.h>
#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object/context_menu_add_render_object_asset.h>

#include "graphics/model_loader/parametric_loader/parametric_interpreter.h"

#include <gui/imgui/imgui.h>

#include <common/unique_ptr.h>
#include <game/game_component.h>

namespace ifx {

GameObjectContextMenu::GameObjectContextMenu(
    std::shared_ptr<SceneRenderer> scene_renderer,
    std::shared_ptr<ResourceContext> resource_creator,
    std::shared_ptr<SceneContainer> scene,
    std::shared_ptr<PhysicsSimulation> physics_simulation) :
    scene_renderer_(scene_renderer),
    resource_creator_(resource_creator),
    scene_(scene) {
    context_menu_add_light_ = ifx::make_unique<ContextMenuAddLight>();
    context_menu_add_render_object_
        = ifx::make_unique<ContextMenuAddRenderObject>();
    context_menu_add_rigid_body_ = ifx::make_unique<ContextMenuAddRigidBody>(
            physics_simulation);
}

GameObjectContextMenuEvent GameObjectContextMenu::Render(std::shared_ptr<
    GameObject> game_object,
                                                         int game_object_id) {
    GameObjectContextMenuEvent event = GameObjectContextMenuEvent::None;
    ImGui::PushID(std::to_string(game_object_id).c_str());
    if (ImGui::BeginPopupContextItem("GameObject context menu")) {

        Add(scene_renderer_, resource_creator_, game_object);
        if(Open(game_object))
            event = GameObjectContextMenuEvent::OpenSoftBodyEditor;
        ImGui::Separator();

        if (Remove(scene_, game_object))
            event = GameObjectContextMenuEvent::Remove;

        ImGui::EndPopup();
    }
    ImGui::PopID();

    return event;
}

void GameObjectContextMenu::Add(std::shared_ptr<SceneRenderer> scene_renderer,
                                std::shared_ptr<ResourceContext> resource_creator,
                                std::shared_ptr<GameObject> game_object) {
    if (ImGui::BeginMenu("Add")) {
        AddLight(resource_creator, game_object);
        AddRenderObject(scene_renderer, resource_creator, game_object);
        AddRigidBody(game_object);
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
        scene_renderer, resource_creator, game_object);
}

void GameObjectContextMenu::AddRigidBody(std::shared_ptr<GameObject> game_object){
    context_menu_add_rigid_body_->Render(game_object);
}

bool GameObjectContextMenu::Open(std::shared_ptr<GameObject> game_object){
    bool return_value = false;
    if (ImGui::BeginMenu("Open")) {
        return_value = OpenInSoftBodyEditor(game_object);
        ImGui::EndMenu();
    }
    return return_value;
}

bool GameObjectContextMenu::OpenInSoftBodyEditor(
        std::shared_ptr<GameObject> game_object){
    bool return_value = false;
    auto render_components =
            game_object->GetComponents(GameComponentType::RENDER);
    if(render_components.size() == 1){
        if (ImGui::Selectable("Soft Body Editor")) {
            return_value = true;
        }
    }
    return return_value;
}

bool GameObjectContextMenu::Remove(std::shared_ptr<SceneContainer> scene,
                                   std::shared_ptr<GameObject> game_object) {
    bool removed = false;
    if (ImGui::Selectable("Remove")) {
        scene->Remove(game_object);
        removed = true;
    }
    return removed;
}

}

