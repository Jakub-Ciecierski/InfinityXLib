#include "editor/views/soft_body_views/soft_body_settings_view.h"

#include <editor/views/soft_body_views/soft_body_structers.h>

#include <gui/imgui/imgui.h>

#include <graphics/rendering/rendering_effect.h>

#include <game/components/render/render_component.h>

namespace ifx {

SoftBodySettingsView::SoftBodySettingsView() :
        render_object_settings_(RenderObjectSettings()){}

void SoftBodySettingsView::Render(SoftBodyObjects& soft_body_objects,
                                  SoftBodyRenderingEffects& rendering_effects){
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
        ImGui::Checkbox("Input", &render_object_settings_.show_input);
        if(render_object_settings_.show_input){
            SetRenderObjectMode(RenderObjectMode::Input);
        }

        ImGui::Checkbox("Output", &render_object_settings_.show_output);
        if(render_object_settings_.show_output){
            SetRenderObjectMode(RenderObjectMode::Output);
        }

        if(soft_body_objects.triangle_mesh){
            soft_body_objects.triangle_mesh->do_render(
                    render_object_settings_.show_input);
        }
        if(soft_body_objects.fem_geometry){
            soft_body_objects.fem_geometry->do_render(
                    render_object_settings_.show_output);
        }

        ImGui::TreePop();
    }
}

void SoftBodySettingsView::RenderMeshingSettings(){
    ImGui::PushItemWidth(50);
    ImGui::SliderFloat("Maximum Volume", &rtfem_options_.maximum_volume,
                       0, 10);
    ImGui::PopItemWidth();
}

void SoftBodySettingsView::SetRenderObjectMode(RenderObjectMode mode){
    render_object_settings_.mode = mode;
    switch(render_object_settings_.mode){
        case RenderObjectMode::Input:
            render_object_settings_.show_input = true;
            render_object_settings_.show_output = false;
            break;
        case RenderObjectMode::Output:
            render_object_settings_.show_input = false;
            render_object_settings_.show_output = true;
            break;
    }
}

}