#include "editor/views/soft_body_views/soft_body_settings_view.h"

#include <editor/views/soft_body_views/soft_body_structers.h>

#include <gui/imgui/imgui.h>

#include <graphics/rendering/rendering_effect.h>

#include <game/components/render/render_component.h>

namespace ifx {

void SoftBodySettingsView::Render(SoftBodyObjects& soft_body_objects,
                                  SoftBodyRenderingEffects& rendering_effects
                                  ){
    RenderShow(rendering_effects, soft_body_objects);
    RenderMeshingSettings();
}

void SoftBodySettingsView::RenderShow(
        SoftBodyRenderingEffects& rendering_effects,
        SoftBodyObjects& soft_body_objects){
    if(ImGui::TreeNodeEx("Show", ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderShowRenderingEffects(rendering_effects);
        RenderShowObjects(soft_body_objects);

        ImGui::TreePop();
    }
}

void SoftBodySettingsView::RenderShowRenderingEffects(
        SoftBodyRenderingEffects& rendering_effects){
    if(ImGui::TreeNodeEx("Rendering Effects",
                         ImGuiTreeNodeFlags_DefaultOpen)){
        RenderShowRenderingEffectCheckbox("Nodes", *rendering_effects.nodes);
        RenderShowRenderingEffectCheckbox("Edges", *rendering_effects.edges);
        RenderShowRenderingEffectCheckbox("Faces", *rendering_effects.faces);
        RenderShowRenderingEffectCheckbox("Textures", *rendering_effects.main);

        ImGui::TreePop();
    }
}

void SoftBodySettingsView::RenderShowRenderingEffectCheckbox(
        std::string name,
        RenderingEffect &rendering_effect){
    static bool enabled;
    enabled = rendering_effect.enabled();
    ImGui::Checkbox(name.c_str(), &enabled);
    rendering_effect.enabled(enabled);
}

void SoftBodySettingsView::RenderShowObjects(
        SoftBodyObjects& soft_body_objects){
    if(ImGui::TreeNodeEx("Objects",
                         ImGuiTreeNodeFlags_DefaultOpen)){
        if(soft_body_objects.triangle_mesh){
            RenderShowObjectCheckbox("Input",
                                     *soft_body_objects.triangle_mesh);
        }
        if(soft_body_objects.fem_geometry){
            RenderShowObjectCheckbox("Output",
                                     *soft_body_objects.fem_geometry);
        }

        ImGui::TreePop();
    }
}

void SoftBodySettingsView::RenderShowObjectCheckbox(
        std::string name,
        RenderComponent& render_component){
    static bool do_render;
    do_render = render_component.do_render();
    ImGui::Checkbox(name.c_str(), &do_render);
    render_component.do_render(do_render);
}

void SoftBodySettingsView::RenderMeshingSettings(){
    ImGui::PushItemWidth(50);
    ImGui::SliderFloat("Maximum Volume", &rtfem_options_.maximum_volume,
                       0, 10);
    ImGui::PopItemWidth();
}

}