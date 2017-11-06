#include "editor/views/scene_views/game_component_views/rigid_body_view.h"

#include <gui/imgui/imgui.h>

namespace ifx {

void RigidBodyView::Render(
        std::shared_ptr<RigidBodyComponent> rigd_body_component){
    if (ImGui::TreeNode("Rigid Body")) {

        ImGui::TreePop();
    }
}

}