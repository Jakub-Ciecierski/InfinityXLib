#include "editor/views/soft_body_views/soft_body_screen_view.h"

#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/shaders/textures/texture.h>

#include <gui/imgui/imgui.h>

namespace ifx {

void SoftBodyScreenView::Render(std::shared_ptr<Renderer> renderer) {
    auto fbo_renderer = std::dynamic_pointer_cast<FBORenderer>(renderer);
    if (!fbo_renderer)
        return;

    const auto &texture = fbo_renderer->GetSceneTexture();
    auto tex_id = texture.id();
    ImTextureID im_tex_id = (ImTextureID) (tex_id);
    auto width_ratio = ImGui::GetColumnWidth() / texture.width();

    ImGui::Image(im_tex_id, ImVec2(texture.width() * width_ratio,
                                   texture.height() * width_ratio));
}

}