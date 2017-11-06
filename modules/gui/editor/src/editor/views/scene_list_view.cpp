#include "editor/views/scene_list_view.h"

#include <graphics/rendering/render_object.h>
#include "graphics/model_loader/parametric_loader/parametric_interpreter.h"

#include <gui/imgui/imgui.h>
#include <gui/imgui/imgui_internal.h>

#include <editor/views/scene_views/game_object_view.h>
#include <editor/views/scene_views/game_component_view.h>
#include <editor/views/scene_views/scene_manipulator_view.h>
#include <editor/views/scene_views/context_menus/game_object_context_menu.h>
#include <editor/views/scene_views/context_menus/game_component_context_menu.h>
#include <editor/views/scene_views/context_menus/scene_list_context_menu.h>
#include "editor/views/scene_views/movable_object_view.h"
#include "editor/views/scene_views/game_component_views/camera_view.h"
#include "editor/views/scene_views/game_component_views/light_view.h"
#include "editor/views/scene_views/game_component_views/render_object_view.h"
#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_light.h>
#include "editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object.h"
#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object/context_menu_add_render_object_parametric_equation.h>
#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object/context_menu_add_render_object_asset.h>
#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_rigid_body.h>
#include "editor/views/scene_views/game_component_views/rigid_body_view.h"

#include <game/scene_container.h>
#include <game/game_component.h>
#include <game/game_object.h>
#include <game/components/cameras/camera_component.h>
#include <game/resources/resource_context.h>

#include <iostream>

#include <common/unique_ptr.h>

namespace ifx {

SceneListView::SceneListView(std::shared_ptr<SceneContainer> scene,
                             std::shared_ptr<ResourceContext> resource_creator,
                             std::shared_ptr<SceneRenderer> scene_renderer,
                             std::shared_ptr<PhysicsSimulation> physics_simulation) :
    View("Scene"),
    scene_(scene),
    resource_creator_(resource_creator),
    selected_game_object_(nullptr),
    selected_game_component_(nullptr) {
    scene_manipulator_ = std::make_shared<SceneManipulator>();

    game_object_view_ = ifx::make_unique<GameObjectView>();
    game_component_view_ = ifx::make_unique<GameComponentView>(scene_renderer);
    scene_manipulator_view_
        = ifx::make_unique<SceneManipulatorView>(scene_manipulator_);
    game_object_context_menu_ = ifx::make_unique<GameObjectContextMenu>(
        scene_renderer,
        resource_creator_,
        scene_,
        physics_simulation);
    game_component_context_menu_ = ifx::make_unique<GameComponentContextMenu>();
    scene_list_context_menu_ = ifx::make_unique<SceneListContextMenu>(scene_);
}

void SceneListView::Render() {
    RenderWindow();
}

void SceneListView::RenderWindow() {
    RenderGameObjectsList();
    ImGui::Separator();
    RenderInspector();
    ImGui::Separator();
    RenderManipulator();
}

void SceneListView::RenderGameObjectsList() {
    if (ImGui::TreeNodeEx("Scene Objects", ImGuiTreeNodeFlags_DefaultOpen)) {
        scene_list_context_menu_->Render();
        RenderGameObjectsList(scene_->game_objects());
        ImGui::TreePop();
    }
}

void SceneListView::RenderInspector() {
    if (ImGui::TreeNodeEx("Inspector", ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderSelectedGameObject();
        RenderSelectedGameComponent();
        ImGui::TreePop();
    }
}

void SceneListView::RenderSelectedGameObject() {
    if (selected_game_object_) {
        if (ImGui::TreeNodeEx("Game Object", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::PushID("0");
            game_object_view_->Render(selected_game_object_);
            ImGui::PopID();
            ImGui::TreePop();
        }
    }
}

void SceneListView::RenderSelectedGameComponent() {
    if (selected_game_component_) {

        if (ImGui::TreeNodeEx("Game Component",
                              ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::PushID("1");
            game_component_view_->Render(selected_game_component_);
            ImGui::PopID();

            ImGui::TreePop();
        }
    }
}

void SceneListView::RenderManipulator() {
    scene_manipulator_view_->Render(selected_game_object_,
                                    scene_->GetActiveCamera());
}

void SceneListView::RenderGameObjectsList(
    std::vector<std::shared_ptr<GameObject>> &game_objects) {
    static int selection_mask = (1 << 2);

    for (unsigned int i = 0; i < game_objects.size(); i++) {
        int node_clicked = -1;
        ImGuiTreeNodeFlags node_flags
            = ImGuiTreeNodeFlags_OpenOnArrow |
                ImGuiTreeNodeFlags_OpenOnDoubleClick |
                ((selection_mask & (1 << i)) ?
                 ImGuiTreeNodeFlags_Selected : 0);
        bool node_open = ImGui::TreeNodeEx((void *) (intptr_t) i,
                                           node_flags,
                                           "GameObject %d", i);
        if (ImGui::IsItemClicked()) {
            node_clicked = i;
        }
        if (node_clicked != -1) {
            selection_mask = (1 << node_clicked);
            SetSelectedGameObject(game_objects[i]);
        }

        auto event = game_object_context_menu_->Render(game_objects[i], i);
        if (event == GameObjectContextMenuEvent::Remove)
            SetSelectedGameObject(nullptr);

        if (node_open) {
            RenderGameComponentsList(game_objects[i], i);
            ImGui::TreePop();
        }
    }
}

void SceneListView::RenderGameComponentsList(
    std::shared_ptr<GameObject> game_object,
    int game_object_id) {
    static int selection_mask = (1 << 2);
    auto game_components = game_object->GetComponents();
    int size = game_components.size();

    // TODO
    const int single_selection_hack = 25;
    int id_start = game_object_id * single_selection_hack;

    for (int i = 0; i < size; i++) {
        int node_clicked = -1;
        int id = id_start + i;
        ImGuiTreeNodeFlags node_flags
            = ImGuiTreeNodeFlags_OpenOnArrow
                | ImGuiTreeNodeFlags_OpenOnDoubleClick
                | ((selection_mask & (1 << id)) ?
                   ImGuiTreeNodeFlags_Selected : 0);

        ImGui::TreeNodeEx((void *) (intptr_t) id,
                          node_flags
                              | ImGuiTreeNodeFlags_Leaf
                              | ImGuiTreeNodeFlags_NoTreePushOnOpen,
                          GetComponentName(game_components[i],
                                           game_object_id, i).c_str(), id);
        if (ImGui::IsItemClicked())
            node_clicked = i;

        if (node_clicked != -1) {
            selection_mask = (1 << (node_clicked + id_start));
            selected_game_component_ = game_components[i];
        }
        auto event = game_component_context_menu_->Render(game_object,
                                                          game_components[i],
                                                          i);
        if (event == GameComponentContextMenuEvent::Remove)
            selected_game_component_ = nullptr;
    }
}

std::string SceneListView::GetComponentName(
    std::shared_ptr<GameComponent> game_component,
    int game_object_id,
    int component_id) {
    std::string str = "";
    //str += std::to_string(game_object_id);
    //str += ".";
    str += std::to_string(component_id);
    str += " [";
    str += GameComponent::GetTypeString(game_component->type());
    str += "]";
    return str;
}

void SceneListView::SetSelectedGameObject(
    std::shared_ptr<GameObject> selected_game_object) {
    selected_game_object_ = selected_game_object;
    NotifySetSelectedGameObject(selected_game_object);
}

} // namespace ifx
