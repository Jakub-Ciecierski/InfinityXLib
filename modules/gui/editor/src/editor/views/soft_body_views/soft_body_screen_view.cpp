#include "editor/views/soft_body_views/soft_body_screen_view.h"

#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/shaders/textures/texture.h>
#include <graphics/rendering/window/window.h>

#include <game/components/cameras/camera_component.h>

#include <editor/views/soft_body_views/picking/ray_casting.h>

#include <gui/imgui/imgui.h>

#include <common/unique_ptr.h>

#include <iostream>

namespace ifx {

SoftBodyScreenView::SoftBodyScreenView() : camera_(nullptr){
    ray_casting_ = ifx::make_unique<RayCasting>();
}

void SoftBodyScreenView::Render(std::shared_ptr<Renderer> renderer) {
    auto fbo_renderer = std::dynamic_pointer_cast<FBORenderer>(renderer);
    if (!fbo_renderer)
        return;

    const auto &texture = fbo_renderer->GetSceneTexture();
    auto tex_id = texture.id();
    ImTextureID im_tex_id = (ImTextureID) (tex_id);
    auto width_ratio = ImGui::GetColumnWidth() / texture.width();

    auto image_width = texture.width() * width_ratio;
    auto image_height = texture.height() * width_ratio;
    ImGui::Image(im_tex_id, ImVec2(image_width, image_height));

    auto image_begin_x = ImGui::GetCursorScreenPos().x;
    auto image_begin_y = ImGui::GetCursorScreenPos().y - image_height;

    auto mouse_x = ImGui::GetMousePos().x;
    auto mouse_y = ImGui::GetMousePos().y;

    auto local_mouse_x = mouse_x - image_begin_x;
    auto local_mouse_y = mouse_y - image_begin_y;

    if(local_mouse_x < 0 || local_mouse_y < 0
        || local_mouse_x > image_width || local_mouse_y > image_height){
        return;
    }
    if(!ray_casting_ || !camera_){
        return ;
    }
    ray_casting_->projection(camera_->getProjectionMatrix());
    ray_casting_->view(camera_->getViewMatrix());
    ray_casting_->window_width(image_width);
    ray_casting_->window_height(image_height);

    std::cout << "In" << std::endl;
    std::cout << local_mouse_x
              << ", "
              << local_mouse_y
              << std::endl;

    std::cout << std::endl;



}

}