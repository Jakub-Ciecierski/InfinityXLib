#include "editor/views/soft_body_views/soft_body_screen_view.h"

#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/shaders/textures/texture.h>
#include <graphics/shaders/data/shader_data.h>
#include <graphics/rendering/window/window.h>
#include <graphics/model/model.h>
#include <graphics/model/mesh.h>

#include <game/components/cameras/camera_component.h>
#include <game/components/render/render_component.h>
#include <game/components/physics/builder/soft_body_fem_component_builder.h>

#include <editor/views/soft_body_views/picking/ray_casting.h>
#include <editor/views/soft_body_views/picking/soft_body_picker.h>
#include "editor/views/soft_body_views/picking/soft_body_node_selection.h"
#include <editor/views/soft_body_views/picking/box_casting.h>

#include <gui/imgui/imgui.h>

#include <common/unique_ptr.h>

#include <math/print_math.h>

#include <iostream>

namespace ifx {

SoftBodyScreenView::SoftBodyScreenView(
    std::shared_ptr<SoftBodyPicker> soft_body_picker) :
    camera_(nullptr),
    picker_(soft_body_picker),
    screen_width_(0),
    screen_height_(0) {}

void SoftBodyScreenView::Render(
    std::shared_ptr<Renderer> renderer,
    SoftBodyFEMComponentBuilder<double>* soft_body_builder) {
    RenderImage(renderer);

    if(soft_body_builder){
        Pick(soft_body_builder,
             ComputeLocalMousePosition());
    }

}

void SoftBodyScreenView::RenderImage(
    std::shared_ptr<Renderer> renderer){
    auto fbo_renderer = std::dynamic_pointer_cast<FBORenderer>(renderer);
    if (!fbo_renderer)
        return;

    const auto &texture = fbo_renderer->GetSceneTexture();
    auto tex_id = texture.id();
    ImTextureID im_tex_id = (ImTextureID) (tex_id);
    auto width_ratio = ImGui::GetColumnWidth() / texture.width();

    screen_width_ = texture.width() * width_ratio;
    screen_height_ = texture.height() * width_ratio;

    ImGui::Image(im_tex_id, ImVec2(screen_width_, screen_height_));
}

glm::vec2 SoftBodyScreenView::ComputeLocalMousePosition(){
    auto image_begin_x = ImGui::GetCursorScreenPos().x;
    auto image_begin_y = ImGui::GetCursorScreenPos().y - screen_height_;

    auto mouse_x = ImGui::GetMousePos().x;
    auto mouse_y = ImGui::GetMousePos().y;

    auto local_mouse_x = mouse_x - image_begin_x;
    auto local_mouse_y = mouse_y - image_begin_y;

    return glm::vec2(local_mouse_x, local_mouse_y);
}

void SoftBodyScreenView::Pick(
    SoftBodyFEMComponentBuilder<double>* soft_body_builder,
    const glm::vec2& mouse_position){
    if (!camera_) {
        return;
    }

    picker_->Pick(soft_body_builder,
                  camera_,
                  screen_width_, screen_height_,
                  mouse_position);
}

std::unique_ptr<Mesh> SoftBodyScreenView::CreateLine(const glm::vec3 &p1,
                                                     const glm::vec3 &p2) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    vertices.push_back(Vertex{
        p1, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)});
    vertices.push_back(Vertex{
        p2, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)});
    indices.push_back(0);
    indices.push_back(1);

    std::unique_ptr<Mesh> mesh(new Mesh(vertices, indices));
    mesh->primitive_draw_mode(PrimitiveDrawMode::LINES);

    return mesh;
}

}