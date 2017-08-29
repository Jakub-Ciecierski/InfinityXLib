#include "editor/views/soft_body_view.h"

#include <game/game_updater.h>
#include <game/game_object.h>
#include <game/scene_container.h>
#include <game/architecture/engine_architecture.h>
#include <game/game_component.h>
#include <game/components/render/render_component.h>
#include "game/resources/resource_context.h"

#include <physics/physics_simulation.h>

#include <gui/imgui/imgui.h>

#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/rendering/scene_renderer.h>
#include <graphics/rendering/rendering_effect.h>
#include <graphics/shaders/textures/texture.h>

#include <RTFEM/FEM/Meshing/Tetrahedralization.h>
#include <RTFEM/FEM/Meshing/TriangleMesh.h>

#include <editor/views/soft_body_views/meshing_builder.h>

namespace ifx{

const unsigned int MAX_RENDER_COMPONENTS = 1;

SoftBodyView::SoftBodyView(std::unique_ptr<GameUpdater> game_updater,
                           const SoftBodyRenderingEffects& rendering_effects) :
        View("Soft Body"),
        game_updater_(std::move(game_updater)),
        rendering_effects_(rendering_effects),
        soft_body_objects_(SoftBodyObjects{nullptr, nullptr, nullptr}),
        first_render_(true){}

bool SoftBodyView::Terminate() {
    game_updater_->engine_architecture()->engine_systems
            .physics_simulation->Terminate();
    return true;
}

void SoftBodyView::Render(){
    game_updater_->Update(1.0f/60.0f);

    ImGui::Columns(2, "Soft");
    RenderSettings();

    ImGui::NextColumn();
    RenderScreen();
/*
    ImGui::NextColumn();
    if(first_render_){
        ImGui::SetColumnOffset(-1, ImGui::GetWindowWidth() - 100);
    }
*/
    ImGui::Columns(1);

    first_render_ = false;
}

void SoftBodyView::RenderSettings(){
    RenderShow();
    RenderMeshingButton();
}

void SoftBodyView::RenderShow(){
    if(ImGui::TreeNodeEx("Show", ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderShowRenderingEffects();
        RenderShowObjects();

        ImGui::TreePop();
    }
}

void SoftBodyView::RenderShowRenderingEffects(){
    if(ImGui::TreeNodeEx("Rendering Effects",
                         ImGuiTreeNodeFlags_DefaultOpen)){
        RenderShowRenderingEffectCheckbox("Nodes", *rendering_effects_.nodes);
        RenderShowRenderingEffectCheckbox("Edges", *rendering_effects_.edges);
        RenderShowRenderingEffectCheckbox("Faces", *rendering_effects_.faces);
        RenderShowRenderingEffectCheckbox("Textures", *rendering_effects_.main);

        ImGui::TreePop();
    }
}

void SoftBodyView::RenderShowRenderingEffectCheckbox(
        std::string name,
        RenderingEffect &rendering_effect){
    static bool enabled;
    enabled = rendering_effect.enabled();
    ImGui::Checkbox(name.c_str(), &enabled);
    rendering_effect.enabled(enabled);
}

void SoftBodyView::RenderShowObjects(){
    if(ImGui::TreeNodeEx("Objects",
                         ImGuiTreeNodeFlags_DefaultOpen)){
        if(soft_body_objects_.triangle_mesh){
            RenderShowObjectCheckbox("Input",
                                     *soft_body_objects_.triangle_mesh);
        }
        if(soft_body_objects_.fem_geometry){
            RenderShowObjectCheckbox("Output",
                                     *soft_body_objects_.fem_geometry);
        }

        ImGui::TreePop();
    }
}

void SoftBodyView::RenderShowObjectCheckbox(std::string name,
                                            RenderComponent& render_component){
    static bool do_render;
    do_render = render_component.do_render();
    ImGui::Checkbox(name.c_str(), &do_render);
    render_component.do_render(do_render);
}

void SoftBodyView::RenderMeshingButton(){
    if(ImGui::Button("Compute 3D Mesh")){
        if(!soft_body_objects_.current_game_object){
            return;
        }
        auto render_components
                = soft_body_objects_.current_game_object->GetComponents(
                        std::move(GameComponentType::RENDER));
        if(render_components.size() != MAX_RENDER_COMPONENTS){
            return;
        }
        MeshingBuilder meshing_builder;

        auto triangle_mesh = meshing_builder.CreateTriangleMesh(
                std::dynamic_pointer_cast<RenderComponent>(render_components[0])
        );

        rtfem::Tetrahedralization<double> tetrahedralization;
        auto fem_geometry = tetrahedralization.Compute(triangle_mesh);

        soft_body_objects_.fem_geometry =
                meshing_builder.CreateRenderComponent(
                        fem_geometry,
                        game_updater_->engine_architecture()->
                                engine_contexts.resource_context->
                                resource_manager());

        RegisterGameObjectToRenderingEffects(soft_body_objects_.fem_geometry);
        soft_body_objects_.current_game_object->Add(
                soft_body_objects_.fem_geometry);
    }
}

void SoftBodyView::RenderScreen(){
    if(first_render_)
        ImGui::SetColumnOffset(-1, 100);

    auto fbo_renderer = std::dynamic_pointer_cast<FBORenderer>(
            game_updater_->engine_architecture()->engine_systems.renderer);
    if(!fbo_renderer)
        return;

    const auto& texture = fbo_renderer->GetSceneTexture();
    auto tex_id = texture.id();
    ImTextureID im_tex_id = (ImTextureID)(tex_id);
    auto width_ratio = ImGui::GetColumnWidth() / texture.width();

    ImGui::Image(im_tex_id, ImVec2(texture.width() * width_ratio,
                                   texture.height() * width_ratio));
}

void SoftBodyView::SetGameObject(
        std::shared_ptr<GameObject> selected_game_object){
    RemoveCurrentGameObject();

    if(!CheckSelectedGameObjectCorrectness(selected_game_object))
        return;

    soft_body_objects_ = CreateNewGameObject(selected_game_object);
}

void SoftBodyView::RemoveCurrentGameObject(){
    auto scene = game_updater_->engine_architecture()->
            engine_systems.scene_container;
    if(soft_body_objects_.current_game_object){
        scene->Remove(soft_body_objects_.current_game_object);
    }
    soft_body_objects_ = SoftBodyObjects{nullptr, nullptr, nullptr};
}

bool SoftBodyView::CheckSelectedGameObjectCorrectness(
        std::shared_ptr<GameObject> selected_game_object){
    if(!selected_game_object){
        soft_body_objects_ = SoftBodyObjects{nullptr, nullptr, nullptr};
        return false;
    }

    auto render_components = selected_game_object->GetComponents(
            std::move(GameComponentType::RENDER));
    if(render_components.size() != MAX_RENDER_COMPONENTS){
        soft_body_objects_ = SoftBodyObjects{nullptr, nullptr, nullptr};
        return false;
    }

    return true;
}

SoftBodyObjects SoftBodyView::CreateNewGameObject(
        std::shared_ptr<GameObject> selected_game_object){
    SoftBodyObjects soft_body_objects;
    auto scene = game_updater_->engine_architecture()->
            engine_systems.scene_container;
    auto render_components = selected_game_object->GetComponents(
            std::move(GameComponentType::RENDER));

    soft_body_objects.current_game_object = scene->CreateAndAddEmptyGameObject();
    for(auto& render_component : render_components){
        soft_body_objects.triangle_mesh = std::make_shared<RenderComponent>(
                std::dynamic_pointer_cast<RenderComponent>(
                        render_component)->models());
        RegisterGameObjectToRenderingEffects(soft_body_objects.triangle_mesh);

        soft_body_objects.current_game_object->Add(
                soft_body_objects.triangle_mesh);
    }
    return soft_body_objects;
}

void SoftBodyView::RegisterGameObjectToRenderingEffects(
        std::shared_ptr<RenderComponent> render_component){
    rendering_effects_.main->RegisterRenderObject(render_component);
    rendering_effects_.edges->RegisterRenderObject(render_component);
    rendering_effects_.nodes->RegisterRenderObject(render_component);
    rendering_effects_.faces->RegisterRenderObject(render_component);
}

void SoftBodyView::OnSetSelectedGameObject(
        std::shared_ptr<GameObject> selected_game_object) {
    SetGameObject(selected_game_object);
}

}