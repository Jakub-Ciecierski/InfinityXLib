#include "editor/views/scene_views/game_component_views/render_object_view.h"

#include <graphics/rendering/render_object.h>
#include <graphics/rendering/scene_renderer.h>
#include <graphics/rendering/rendering_effect.h>

#include <game/components/render/render_component.h>

#include <gui/imgui/imgui.h>

namespace ifx{

RenderObjectView::RenderObjectView(std::shared_ptr<SceneRenderer> scene_renderer) :
        scene_renderer_(scene_renderer) {}

void RenderObjectView::Render(std::shared_ptr<RenderComponent> render_object){
    if (ImGui::TreeNode("Rendering Effects")) {
        RenderRenderingEffectsContextMenu(render_object);
        RenderList(render_object);
        ImGui::TreePop();
    }
}

void RenderObjectView::RenderRenderingEffectsContextMenu(std::shared_ptr<RenderComponent> render_object){
    if (ImGui::BeginPopupContextItem("Rendering Effects Context Menu")) {
        if(ImGui::BeginMenu("Add")){
            auto& rendering_effects = scene_renderer_->rendering_effects();
            for(unsigned int i = 0; i < rendering_effects.size(); i++){
                if(ImGui::Selectable(GetBaseName(rendering_effects[i]->name()).c_str())){
                    rendering_effects[i]->RegisterRenderObject(render_object);
                }
            }
            ImGui::EndMenu();
        }
        ImGui::EndPopup();
    }
}

void RenderObjectView::RenderList(std::shared_ptr<RenderComponent> render_object){
    auto rendering_effects = render_object->rendering_effects();

    static int selection_mask = (1 << 2);
    for(unsigned int i = 0;i < rendering_effects.size(); i++){
        int node_clicked = -1;
        ImGuiTreeNodeFlags node_flags
                = ImGuiTreeNodeFlags_Bullet | ((selection_mask & (1 << i)) ?
                                               ImGuiTreeNodeFlags_Selected : 0);
        bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i,
                                           node_flags,
                                           GetBaseName(rendering_effects[i]->name()).c_str());
        if (ImGui::IsItemClicked()){
            node_clicked = i;
        }
        if (node_clicked != -1){
            selection_mask = (1 << node_clicked);
        }
        ImGui::PushID(i);
        RenderRenderingEffectContextMenu(rendering_effects[i],
                                         render_object);
        ImGui::PopID();

        if (node_open){
            ImGui::TreePop();
        }
    }
}

void RenderObjectView::RenderRenderingEffectContextMenu(RenderingEffect* rendering_effect,
                                                        std::shared_ptr<RenderComponent> render_object){
    if (ImGui::BeginPopupContextItem("Rendering Effect Context Menu")) {
        if(ImGui::Selectable("Remove")){
            rendering_effect->DeregisterRenderObject(render_object);
        }
        ImGui::EndPopup();
    }
}

std::string RenderObjectView::GetBaseName(const std::string& name){
    std::string base_name = "";
    for(unsigned int i = 0; i < name.length(); i++){
        if(name[i] == '.')
            break;
        base_name += name[i];
    }
    return base_name;
}

}