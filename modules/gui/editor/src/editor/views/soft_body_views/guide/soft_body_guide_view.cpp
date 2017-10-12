#include "editor/views/soft_body_views/guide/soft_body_guide_view.h"

#include <editor/views/soft_body_views/soft_body_structers.h>

#include <gui/imgui/imgui.h>

#include <game/game_object.h>

namespace ifx {

void SoftBodyGuideView::Render(const SoftBodyObjects &soft_body_objects){
    RenderSelectorInfo(soft_body_objects);
    RenderScreenInfo();
    RenderMeshingInfo();
    RenderMaterialInfo();
    RenderBoundaryConditionsInfo();
    RenderLoadInfo();
    RenderRenderingInfo();
    RenderSolverInfo();
}

void SoftBodyGuideView::RenderSelectorInfo(
    const SoftBodyObjects &soft_body_objects){
    std::string current_game_object_name = "None selected / Incorrect";
    if(soft_body_objects.current_game_object){
        current_game_object_name = "Selected correct";
    }

    std::vector<std::string> lines = {
        "Select Game Object from the Scene Hierarchy.",
        "In order to create Soft Body, selected Game Object must have exactly"
            " one Render Component. Other Components can be included (e.g. "
            "Light).",
        "Click the above bottom (Guide) to choose tab. Brief description of "
            "each tab is given bellow",
        "Currently selected Game Object: " + current_game_object_name + "."
    };
    RenderParagraphText("Selector", lines);
}

void SoftBodyGuideView::RenderScreenInfo(){
    std::vector<std::string> lines = {
        "On the right You should see screen with selected Game Object.",
        "Left mouse button: hold to rotate.",
        "Right mouse button: hold to zoom in/out.",
        "Scroll: to zoom in/out.",
        "Middle Mouse: hold to move camera.",
    };
    RenderParagraphText("Screen", lines);
}

void SoftBodyGuideView::RenderMeshingInfo(){
    std::vector<std::string> lines = {
        "You can create 3D mesh of finite elements. Only Tetrahedron are "
            "supported."
    };
    RenderParagraphText("Meshing tab", lines);
}

void SoftBodyGuideView::RenderMaterialInfo(){
    std::vector<std::string> lines = {
        "Choose material properties used in FEM Model."
    };
    RenderParagraphText("Material tab", lines);
}

void SoftBodyGuideView::RenderBoundaryConditionsInfo(){
    std::vector<std::string> lines = {
        "Impose Boundary Conditions of displacement on any vertex in the FEM "
            "Model."
    };
    RenderParagraphText("Boundary Conditions tab", lines);
}

void SoftBodyGuideView::RenderLoadInfo(){
    std::vector<std::string> lines = {
        "Impose body (e.g. gravity) or traction (e.g. contact) forces on the "
            "FEM Model.",
        "Imposed load should probably be mainly used for developing the "
            "current soft body.",
        "Load in Soft Body editor is independent of any physics properties "
            "set in physics simulation of the main editor (e.g. gravity). "
            "Thus the gravity set in the physics simulation panel will not "
            "effect solver run in the soft body editor."
    };
    RenderParagraphText("Load tab", lines);
}

void SoftBodyGuideView::RenderRenderingInfo(){
    std::vector<std::string> lines = {
        "Select shaders for rendering of current soft body.",
        "Choose to render input (selected game object) or output (soft body "
            "in creation)."
    };
    RenderParagraphText("Rendering tab", lines);
}

void SoftBodyGuideView::RenderSolverInfo(){
    std::vector<std::string> lines = {
        "Choose solver type (e.g. static/dynamic).",
        "Solve the FEM Model.",
    };
    RenderParagraphText("Solver tab", lines);
}

void SoftBodyGuideView::RenderParagraphText(
    std::string paragraph_name,
    const std::vector<std::string>& lines){
    ImGui::Bullet();
    ImGui::SameLine();
    ImGui::TextWrapped(paragraph_name.c_str());

    for(auto& line : lines)
        ImGui::TextWrapped(line.c_str());
}

void SoftBodyGuideView::RenderParagraphText(std::string text){
    ImGui::Bullet();
    ImGui::SameLine();
    ImGui::Text(text.c_str());
}

}