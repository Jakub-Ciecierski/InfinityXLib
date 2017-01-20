#include <gui/imgui/imgui.h>
#include "engine_gui/views/scene_view/game_component_views/rigid_body_view.h"
#include <physics/rigid_body.h>

#include <math/math_ifx.h>

namespace ifx{

RigidBodyView::RigidBodyView(){}
RigidBodyView::~RigidBodyView(){}

void RigidBodyView::Render(std::shared_ptr<RigidBody> rigid_body){
    if(ImGui::TreeNode("Rigid Body")){
        RenderLinearVelocity(rigid_body);
        ImGui::TreePop();
    }
}

void RigidBodyView::RenderLinearVelocity(std::shared_ptr<RigidBody> rigid_body){
    static float raw[3];
    glm::vec3 vel = rigid_body->GetLinearVelocity();

    raw[0] = vel.x;
    raw[1] = vel.y;
    raw[2] = vel.z;

    ImGui::SliderFloat3("Linear Velocity", raw, -10, 10);
    rigid_body->SetLinearVelocity((glm::vec3(raw[0], raw[1], raw[2])));
}

}