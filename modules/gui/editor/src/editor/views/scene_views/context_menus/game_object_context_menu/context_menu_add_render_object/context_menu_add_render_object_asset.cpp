#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object/context_menu_add_render_object_asset.h>

#include <game/game_object.h>
#include <game/resources/resource_context.h>
#include <game/components/render/render_component.h>

#include <graphics/rendering/scene_renderer.h>
#include <graphics/model/model_creator.h>
#include <graphics/rendering/rendering_effect.h>
#include <graphics/model_loader/model_loader.h>

#include <resources/resource_manager.h>
#include "resources/resource_finder.h"

#include <gui/imgui/imgui.h>

namespace ifx {

ContextMenuAddRenderObjectAsset::ContextMenuAddRenderObjectAsset() :
        selected_asset_(-1){}

void ContextMenuAddRenderObjectAsset::Render(
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<ResourceContext> resource_creator,
        std::shared_ptr<GameObject> game_object){
    if (ImGui::Button("Assets")) {
        ImGui::OpenPopup("Assets");
    }
    if (ImGui::BeginPopupModal("Assets", NULL,
                               ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::BeginChild(ImGui::GetID((void *) (intptr_t) 0),
                          ImVec2(1800 / 2.0f, 1200 / 2.0f), false,
                          ImGuiWindowFlags_HorizontalScrollbar);

        RenderAssetList(
                resource_creator->resource_manager()->resource_finders()
                        .model_finder_->found_resources());
        ImGui::EndChild();
        ImGui::Separator();

        RenderFooter(scene_renderer, resource_creator, game_object);

        ImGui::EndPopup();
    }
}

void ContextMenuAddRenderObjectAsset::RenderAssetList(
        const std::vector<std::string>& models){
    static int selection_mask = (1 << 2);

    for (unsigned int i = 0; i < models.size(); i++) {
        int node_clicked = -1;
        ImGuiTreeNodeFlags node_flags
                = ImGuiTreeNodeFlags_Bullet | ((selection_mask & (1 << i)) ?
                                               ImGuiTreeNodeFlags_Selected
                                                                           : 0);
        bool node_open = ImGui::TreeNodeEx((void *) (intptr_t) i,
                                           node_flags,
                                           models[i].c_str());
        if (ImGui::IsItemClicked()) {
            node_clicked = i;
        }
        if (node_clicked != -1) {
            selection_mask = (1 << node_clicked);
            selected_asset_ = i;
        }

        if (node_open) {
            ImGui::TreePop();
        }
    }
}

void ContextMenuAddRenderObjectAsset::RenderFooter(
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<ResourceContext> resource_creator,
        std::shared_ptr<GameObject> game_object){
    if (ImGui::Button("OK", ImVec2(120, 0))) {
        auto render_component = CreateRenderComponent(
                scene_renderer, resource_creator
        );
        if(render_component){
            game_object->Add(render_component);
        }

        ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel", ImVec2(120, 0))) {
        ImGui::CloseCurrentPopup();
    }
}

std::shared_ptr<RenderComponent>
ContextMenuAddRenderObjectAsset::CreateRenderComponent(
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<ResourceContext> resource_creator){
    if(selected_asset_ > -1){
        auto assset_name =
                resource_creator->resource_manager()->
                        resource_finders().
                        model_finder_->found_resources()[selected_asset_];
        ModelLoader model_loader(assset_name,
                                 resource_creator->model_creator(),
                                 resource_creator->texture_creator());
        auto model = model_loader.loadModel();
        if(!model){
            return nullptr;
        }
        auto render_object = std::make_shared<RenderComponent>(model);
        if (scene_renderer->default_rendering_effect()) {
            scene_renderer->default_rendering_effect()->RegisterRenderObject(
                    render_object);
        }
        return render_object;
    }
    return nullptr;
}

}