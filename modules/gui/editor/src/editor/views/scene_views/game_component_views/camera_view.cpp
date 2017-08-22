#include "editor/views/scene_views/game_component_views/camera_view.h"

#include <graphics/rendering/camera/camera.h>
#include <game/components/cameras/camera_component.h>

#include <gui/imgui/imgui.h>

namespace ifx{

void CameraView::Render(std::shared_ptr<CameraComponent> camera){
    if(ImGui::TreeNode("Camera")){
        ImGui::PushItemWidth(150);
        {
            static float near = 0;
            near = camera->near_plane();
            if(ImGui::SliderFloat("Near Plane", &near, 0.01, 100))
                camera->near_plane(near);

            static float far = 0;
            far = camera->far_plane();
            if(ImGui::SliderFloat("Far Plane", &far, 1, 10000))
                camera->far_plane(far);
        }

        ImGui::PopItemWidth();

        ImGui::TreePop();
    }
}

}