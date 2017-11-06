#include "editor/views/scene_views/game_component_views/rigid_body_view.h"

#include <game/components/physics/rigid_body_component.h>

#include <gui/imgui/imgui.h>
#include <physics/collision/collision_shape.h>

namespace ifx {

void RigidBodyView::Render(
        std::shared_ptr<RigidBodyComponent> rigd_body_component){
    if (ImGui::TreeNodeEx("Rigid Body",
                          ImGuiTreeNodeFlags_DefaultOpen)) {

        ImGui::PushItemWidth(70);
        RenderCollisionShape(*rigd_body_component);
        RenderMass(*rigd_body_component);
        RenderPhysicsMaterial(*rigd_body_component);
        ImGui::PopItemWidth();

        ImGui::TreePop();
    }
}

void RigidBodyView::RenderCollisionShape(RigidBodyComponent& rigd_body_component){
    auto name =
            CollisionShapeName(rigd_body_component.collision_shape()->type());

    if (ImGui::TreeNodeEx(name.c_str(),
                          ImGuiTreeNodeFlags_DefaultOpen)) {

        ImGui::TreePop();
    }
}

void RigidBodyView::RenderMass(RigidBodyComponent& rigd_body_component){
    if (ImGui::TreeNodeEx("Mass", ImGuiTreeNodeFlags_DefaultOpen)) {
        float mass = rigd_body_component.mass();
        if(ImGui::InputFloat("Mass", &mass)){
            rigd_body_component.mass(mass);
        }

        ImGui::TreePop();
    }
}

void RigidBodyView::RenderPhysicsMaterial(RigidBodyComponent& rigd_body_component){
    if (ImGui::TreeNodeEx("Physics Material",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        auto physics_material = rigd_body_component.physics_material();

        bool value_changed = false;
        if(ImGui::InputFloat("Dynamic Friction",
                             &physics_material.dynamic_friction)){
            value_changed = true;
        }
        if(ImGui::InputFloat("Static Friction",
                             &physics_material.static_friction)){
            value_changed = true;
        }
        if(ImGui::InputFloat("Restitution", &physics_material.restitution)){
            value_changed = true;
        }

        if(value_changed){
            rigd_body_component.physics_material(physics_material);
        }

        ImGui::TreePop();
    }
}

}