#include "editor/views/soft_body_views/scene_builder/soft_body_scene_builder.h"

#include <game/game_object.h>
#include <game/game_component.h>
#include <game/components/physics/builder/soft_body_fem_component_builder.h>
#include <game/components/physics/soft_body_fem_component.h>
#include <game/components/render/render_component.h>

#include <graphics/rendering/scene_renderer.h>
#include <graphics/rendering/rendering_effect.h>

#include <gui/imgui/imgui.h>

namespace ifx {

SoftBodySceneBuilder::SoftBodySceneBuilder(
        std::shared_ptr<SceneRenderer> scene_renderer) :
        scene_renderer_(scene_renderer){}

void SoftBodySceneBuilder::Render(
        std::shared_ptr<GameObject> game_object,
        SoftBodyFEMComponentBuilder<double>* soft_body_builder){
    RenderBuild(game_object, soft_body_builder);
    RenderInfo();
}

void SoftBodySceneBuilder::RenderBuild(
        std::shared_ptr<GameObject> game_object,
        SoftBodyFEMComponentBuilder<double>* soft_body_builder){
    if(ImGui::Button("Build")){
        auto rigid_components =
                game_object->GetComponents(GameComponentType::PHYSICS);
        for(auto& rigid_component : rigid_components){
            game_object->Remove(rigid_component);
        }

        auto render_components =
                game_object->GetComponents(GameComponentType::RENDER);
        for(auto& render_component : render_components){
            game_object->Remove(render_component);
        }

        auto fem_soft_body = soft_body_builder->Build();

        scene_renderer_->default_rendering_effect()->RegisterRenderObject(
                fem_soft_body->render_component());

        game_object->Add(fem_soft_body);
        game_object->Add(fem_soft_body->render_component());
    }
}

void SoftBodySceneBuilder::RenderInfo(){
    ImGui::Bullet();
    ImGui::SameLine();
    ImGui::TextWrapped(
            "Building FEM Soft Body into currently selected Game Object");

    ImGui::Bullet();
    ImGui::SameLine();
    ImGui::TextWrapped("Removing all Rigid Body components");

    ImGui::Bullet();
    ImGui::SameLine();
    ImGui::TextWrapped(
            "Replacing Render component with new based on FEM surface Mesh");
}

}