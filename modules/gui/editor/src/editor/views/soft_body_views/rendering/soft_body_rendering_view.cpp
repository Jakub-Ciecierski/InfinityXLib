#include "editor/views/soft_body_views/rendering/soft_body_rendering_view.h"

#include <editor/views/soft_body_views/soft_body_structers.h>
#include <editor/views/soft_body_views/meshing/meshing_builder.h>

#include <gui/imgui/imgui.h>

#include <graphics/rendering/rendering_effect.h>

#include <game/components/render/render_component.h>

namespace ifx {

SoftBodyRenderingView::SoftBodyRenderingView() :
    render_object_settings_(RenderObjectSettings()) {}

void SoftBodyRenderingView::Render(SoftBodyEditorObjects &soft_body_objects,
                                   SoftBodyRenderingEffects &rendering_effects) {
    RenderShowRenderingEffects(rendering_effects);
    RenderShowObjects(soft_body_objects);
}

void SoftBodyRenderingView::RenderShowRenderingEffects(
    SoftBodyRenderingEffects &rendering_effects) {
    if (ImGui::TreeNodeEx("Rendering Effects",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderShowRenderingEffectCheckbox("Nodes", *rendering_effects.nodes);
        RenderShowRenderingEffectCheckbox("Edges", *rendering_effects.edges);
        RenderShowRenderingEffectCheckbox("Faces", *rendering_effects.faces);
        RenderShowRenderingEffectCheckbox("Textures", *rendering_effects.main);

        ImGui::TreePop();
    }
}

void SoftBodyRenderingView::RenderShowRenderingEffectCheckbox(
    std::string name,
    RenderingEffect &rendering_effect) {
    static bool enabled;
    enabled = rendering_effect.enabled();
    ImGui::Checkbox(name.c_str(), &enabled);
    rendering_effect.enabled(enabled);
}

void SoftBodyRenderingView::RenderShowObjects(
    SoftBodyEditorObjects &soft_body_objects) {
    if (ImGui::TreeNodeEx("Objects",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Checkbox("Input", &render_object_settings_.show_input);
        if (render_object_settings_.show_input) {
            SetRenderObjectMode(RenderObjectMode::Input);
        }

        ImGui::Checkbox("Output", &render_object_settings_.show_output);
        if (render_object_settings_.show_output) {
            SetRenderObjectMode(RenderObjectMode::Output);
        }

        UpdateRenderObjectMode(soft_body_objects);

        ImGui::TreePop();
    }
}

void SoftBodyRenderingView::SetRenderObjectMode(RenderObjectMode mode) {
    render_object_settings_.mode = mode;
    switch (render_object_settings_.mode) {
        case RenderObjectMode::Input:render_object_settings_.show_input = true;
            render_object_settings_.show_output = false;
            break;
        case RenderObjectMode::Output:
            render_object_settings_.show_input = false;
            render_object_settings_.show_output = true;
            break;
    }
}

void SoftBodyRenderingView::UpdateRenderObjectMode(
    SoftBodyEditorObjects &soft_body_objects){
    if (soft_body_objects.rigid_body_triangle_mesh) {
        soft_body_objects.rigid_body_triangle_mesh->do_render(
            render_object_settings_.show_input);
    }
    if (soft_body_objects.soft_body_fem_render) {
        soft_body_objects.soft_body_fem_render->do_render(
            render_object_settings_.show_output);
    }
}

}