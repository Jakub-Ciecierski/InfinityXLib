#include "engine_gui/views/scene_view.h"

#include <game/scene_container.h>
#include <object/render_object.h>

#include <gui/imgui/imgui.h>
#include <gui/imgui/imgui_internal.h>
#include <iostream>
#include <object/game_component.h>
#include <object/game_object.h>
#include <engine_gui/views/scene_view/game_object_view.h>
#include <engine_gui/views/scene_view/game_component_view.h>
#include <engine_gui/views/scene_view/scene_manipulator_view.h>

namespace ifx {

SceneView::SceneView(std::shared_ptr<SceneContainer> scene) :
        scene_(scene),
        selected_game_object_(nullptr),
        selected_game_component_(nullptr){
    game_object_view_.reset(new GameObjectView());
    game_component_view_.reset(new GameComponentView());
    scene_manipulator_view_.reset(new SceneManipulatorView());
}

SceneView::~SceneView(){ }

void SceneView::Render(){
    RenderWindow();
}

void SceneView::RenderWindow(){
    if(!show_)
        return;
    ImGui::Begin("Scene");
    RenderGameObjectsList();
    RenderSelectedGameObject();
    RenderSelectedGameComponent();
    RenderManipulator();
    ImGui::End();
}

void SceneView::RenderGameObjectsList(){
    if (ImGui::CollapsingHeader("Scene Objects")) {
        RenderGameObjectsList(scene_->game_objects());
    }
}

void SceneView::RenderSelectedGameObject(){
    if (selected_game_object_) {
        if (ImGui::CollapsingHeader("Selected Game Object")) {
            ImGui::PushID("0");
            game_object_view_->Render(selected_game_object_, scene_);
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
    if (selected_game_object_) {
        (ImGui::CollapsingHeader("Manipulator"));
        {
            auto active_camera = scene_->GetActiveCamera();
            if (active_camera) {
                scene_manipulator_view_->Render(selected_game_object_,
                                                active_camera);
            }
        }
    }
}

void SceneView::RenderGameObjectsList(
        std::vector<std::shared_ptr<GameObject>>& game_objects){
    if (ImGui::TreeNode("Game Objects")){
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
            if (node_open){
                RenderGameComponentsList(game_objects[i], i);
                ImGui::TreePop();
            }
            if (node_clicked != -1){
                selection_mask = (1 << node_clicked);
                selected_game_object_ = game_objects[i];
            }
        }
        ImGui::TreePop();
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
