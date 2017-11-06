#include "editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_rigid_body.h"

#include <gui/imgui/imgui.h>

#include <physics/physics_simulation.h>
#include <physics/rigid_body/impl/rigid_body_impl.h>
#include <physics/collision/shapes/box_collision_shape.h>
#include <physics/collision/shapes/sphere_collision_shape.h>
#include <physics/collision/shapes/static_plane_shape.h>

#include <game/components/physics/rigid_body_component.h>
#include <game/game_object.h>

namespace ifx {

ContextMenuAddRigidBody::ContextMenuAddRigidBody(
        std::shared_ptr<PhysicsSimulation> physics_simulation) :
        physics_simulation_(physics_simulation),
        collision_shape_type_(CollisionShapeType::Box),
        mass_(1){}

void ContextMenuAddRigidBody::Render(std::shared_ptr<GameObject> game_object){
    if (ImGui::BeginMenu("Rigid Body")) {

        RenderPopWindow(game_object);

        ImGui::EndMenu();
    }
}

void ContextMenuAddRigidBody::RenderPopWindow(std::shared_ptr<GameObject> game_object){
    if (ImGui::Button("Add")) {
        ImGui::OpenPopup("Add");
    }
    if (ImGui::BeginPopupModal("Add", NULL,
                               ImGuiWindowFlags_AlwaysAutoResize)) {
        RenderCollisionType();
        ImGui::Separator();

        if(colliders_selectables_.selected !=
                colliders_selectables_.static_plane_id){
            RenderMass();
        }

        RenderFooter(game_object);

        ImGui::EndPopup();
    }
}

void ContextMenuAddRigidBody::RenderMass(){
    ImGui::PushItemWidth(70);
    ImGui::InputFloat("Mass", &mass_);
    ImGui::PopItemWidth();
}

void ContextMenuAddRigidBody::RenderCollisionType(){
    if (ImGui::Button(colliders_selectables_.names[colliders_selectables_.selected].c_str(),
                      ImVec2(100, 20))){
        ImGui::OpenPopup("select");
    }

    if (ImGui::BeginPopup("select")) {
        for (unsigned int i = 0; i < colliders_selectables_.names.size(); i++){
            if (ImGui::Selectable(colliders_selectables_.names[i].c_str())){
                colliders_selectables_.selected = i;
            }
        }
        ImGui::EndPopup();
    }

    RenderCollisionData();
}

void ContextMenuAddRigidBody::RenderCollisionData(){
    switch(colliders_selectables_.selected){
        case colliders_selectables_.box_id:
            RenderBoxConstructionData();
            break;
        case colliders_selectables_.sphere_id:
            RenderSphereConstructionData();
            break;
        case colliders_selectables_.static_plane_id:
            RenderStaticPlaneConstructionData();
            break;
    }
}

void ContextMenuAddRigidBody::RenderBoxConstructionData(){
    float box_dim_raw[3];
    box_dim_raw[0] = box_construction_data_.box_dim.x;
    box_dim_raw[1] = box_construction_data_.box_dim.y;
    box_dim_raw[2] = box_construction_data_.box_dim.z;

    ImGui::PushItemWidth(150);
    ImGui::InputFloat3("Dimension", box_dim_raw);
    ImGui::PopItemWidth();

    box_construction_data_.box_dim.x = box_dim_raw[0];
    box_construction_data_.box_dim.y = box_dim_raw[1];
    box_construction_data_.box_dim.z = box_dim_raw[2];
}

void ContextMenuAddRigidBody::RenderSphereConstructionData(){
    ImGui::PushItemWidth(70);
    ImGui::InputFloat("radius", &sphere_construction_data_.radius);
    ImGui::PopItemWidth();
}

void ContextMenuAddRigidBody::RenderStaticPlaneConstructionData(){
    float box_dim_raw[3];
    box_dim_raw[0] = static_plane_construction_data_.plane_normal.x;
    box_dim_raw[1] = static_plane_construction_data_.plane_normal.y;
    box_dim_raw[2] = static_plane_construction_data_.plane_normal.z;

    ImGui::PushItemWidth(150);
    ImGui::InputFloat3("Normal", box_dim_raw);
    ImGui::PopItemWidth();

    ImGui::PushItemWidth(70);
    ImGui::InputFloat("Constant", &static_plane_construction_data_
            .plane_constant);
    ImGui::PopItemWidth();

    static_plane_construction_data_.plane_normal.x = box_dim_raw[0];
    static_plane_construction_data_.plane_normal.y = box_dim_raw[1];
    static_plane_construction_data_.plane_normal.z = box_dim_raw[2];
}

void ContextMenuAddRigidBody::RenderFooter(std::shared_ptr<GameObject> game_object){
    ImGui::Separator();
    if (ImGui::Button("OK", ImVec2(60, 0))) {
        game_object->Add(Create());
        ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel", ImVec2(60, 0))) {
        ImGui::CloseCurrentPopup();
    }
}

std::shared_ptr<RigidBodyComponent> ContextMenuAddRigidBody::Create(){
    auto rigid_body = std::shared_ptr<ifx::RigidBodyComponent>(
            new RigidBodyComponent(
                    physics_simulation_,
                    CreateRigidBodyParams()));

    return rigid_body;
}

RigidBodyParams ContextMenuAddRigidBody::CreateRigidBodyParams(){
    switch(colliders_selectables_.selected){
        case colliders_selectables_.box_id: {
            auto box_collision = std::make_shared<BoxCollisionShape>(
                    box_construction_data_.box_dim);
            return RigidBodyParams{box_collision, mass_};
        }
        case colliders_selectables_.sphere_id:{
            auto sphere_collision = std::make_shared<SphereCollisionShape>(
                    sphere_construction_data_.radius);
            return RigidBodyParams{sphere_collision, mass_};
        }
        case colliders_selectables_.static_plane_id: {
            auto plane_collision = std::make_shared<StaticPlaneShape>(
                    static_plane_construction_data_.plane_normal,
                    static_plane_construction_data_.plane_constant);
            return RigidBodyParams{plane_collision, 0};
        }
        default:
            return RigidBodyParams{nullptr, mass_};
    }
}

}
