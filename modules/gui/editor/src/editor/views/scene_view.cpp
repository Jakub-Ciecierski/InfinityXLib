#include "editor/views/scene_view.h"

#include <graphics/rendering/render_object.h>

#include <gui/imgui/imgui.h>
#include <gui/imgui/imgui_internal.h>

#include <editor/views/scene_views/game_object_view.h>
#include <editor/views/scene_views/game_component_view.h>
#include <editor/views/scene_views/scene_manipulator_view.h>
#include <editor/views/scene_views/context_menus/game_object_context_menu.h>
#include <editor/views/scene_views/context_menus/game_component_context_menu.h>
#include <editor/views/scene_views/context_menus/scene_list_context_menu.h>

#include <game/scene_container.h>
#include <game/game_component.h>
#include <game/game_object.h>
#include <game/components/cameras/camera_component.h>

#include <game/resources/resource_context.h>
#include <iostream>

namespace ifx {

SceneView::SceneView(std::shared_ptr<SceneContainer> scene,
                     std::shared_ptr<ResourceContext> resource_creator,
                     std::shared_ptr<SceneRenderer> scene_renderer) :
        View("Scene"),
        scene_(scene),
        resource_creator_(resource_creator),
        selected_game_object_(nullptr),
        selected_game_component_(nullptr) {
    scene_manipulator_
            = std::shared_ptr<SceneManipulator>(new SceneManipulator());
    game_object_view_.reset(new GameObjectView());
    game_component_view_.reset(new GameComponentView(scene_renderer));
    scene_manipulator_view_.reset(new SceneManipulatorView(scene_manipulator_));

    game_object_context_menu_.reset(new GameObjectContextMenu(scene_renderer,
                                                              resource_creator_, scene_));
    game_component_context_menu_.reset(new GameComponentContextMenu());
    scene_list_context_menu_.reset(new SceneListContextMenu(scene_));
}

SceneView::~SceneView(){ }

void SceneView::Render(){
    RenderWindow();
}

void SceneView::RenderWindow(){
    RenderGameObjectsList();
    RenderSelectedGameObject();
    RenderSelectedGameComponent();
    RenderManipulator();
}

void SceneView::RenderGameObjectsList(){
    if (ImGui::CollapsingHeader("Scene Objects")) {
        scene_list_context_menu_->Render();
        RenderGameObjectsList(scene_->game_objects());
    }
}

void SceneView::RenderSelectedGameObject(){
    if (selected_game_object_) {
        if (ImGui::CollapsingHeader("Selected Game Object")) {
            ImGui::PushID("0");
            game_object_view_->Render(selected_game_object_);
            ImGui::PopID();
        }
    }
}

void SceneView::RenderSelectedGameComponent(){
    if (selected_game_component_) {
        if (ImGui::CollapsingHeader("Selected Game Component")) {
            ImGui::PushID("1");
            game_component_view_->Render(selected_game_component_);
            ImGui::PopID();
        }
    }
}

void SceneView::RenderManipulator(){
    scene_manipulator_view_->Render(selected_game_object_,
                                    scene_->GetActiveCamera());
}

void SceneView::RenderGameObjectsList(
        std::vector<std::shared_ptr<GameObject>>& game_objects){
    static int selection_mask = (1 << 2);

    for(int i = 0;i < game_objects.size(); i++){
        int node_clicked = -1;
        ImGuiTreeNodeFlags node_flags
                = ImGuiTreeNodeFlags_OpenOnArrow |
                        ImGuiTreeNodeFlags_OpenOnDoubleClick |
                        ((selection_mask & (1 << i)) ?
                         ImGuiTreeNodeFlags_Selected : 0);
        bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i,
                                           node_flags,
                                           "GameObject %d", i);
        if (ImGui::IsItemClicked()){
            node_clicked = i;
        }
        if (node_clicked != -1){
            selection_mask = (1 << node_clicked);
            selected_game_object_ = game_objects[i];
        }

        game_object_context_menu_->Render(game_objects[i], i);

        if (node_open){
            RenderGameComponentsList(game_objects[i], i);
            ImGui::TreePop();
        }
    }
}

void SceneView::RenderGameComponentsList(
        std::shared_ptr<GameObject> game_object,
        int game_object_id){
    static int selection_mask = (1 << 2);
    auto game_components = game_object->GetComponents();
    int size = game_components.size();

    // TODO
    const int single_selection_hack = 25;
    int id_start = game_object_id * single_selection_hack;

    for(int i = 0; i < size; i++){
        int node_clicked = -1;
        int id = id_start+i;
        ImGuiTreeNodeFlags node_flags
                = ImGuiTreeNodeFlags_OpenOnArrow
                  | ImGuiTreeNodeFlags_OpenOnDoubleClick
                  | ((selection_mask & (1 << id)) ?
                     ImGuiTreeNodeFlags_Selected : 0);

        ImGui::TreeNodeEx((void*)(intptr_t)id,
                          node_flags
                          | ImGuiTreeNodeFlags_Leaf
                          | ImGuiTreeNodeFlags_NoTreePushOnOpen,
                          GetComponentName(game_components[i],
                                           game_object_id,i).c_str(), id);
        if (ImGui::IsItemClicked())
            node_clicked = i;

        if (node_clicked != -1){
            selection_mask = (1 << node_clicked + id_start);
            selected_game_component_ = game_components[i];
        }
        game_component_context_menu_->Render(game_object, game_components[i], i);
    }
}

std::string SceneView::GetComponentName(
        std::shared_ptr<GameComponent> game_component,
        int game_object_id,
        int component_id){
    std::string str = "";
    //str += std::to_string(game_object_id);
    //str += ".";
    str += std::to_string(component_id);
    str += " [";
    str += GameComponent::GetTypeString(game_component->type());
    str += "]";
    return str;
}

} // namespace ifx
