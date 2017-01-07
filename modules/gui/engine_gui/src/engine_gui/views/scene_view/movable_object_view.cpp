#include <gui/imgui/imgui.h>
#include "engine_gui/views/scene_view/movable_object_view.h"

#include <object/movable_object.h>
#include <math/math_ifx.h>

namespace ifx{

MovableObjectView::MovableObjectView(){}
MovableObjectView::~MovableObjectView(){}

void MovableObjectView::Render(std::shared_ptr<MovableObject> movable_object){
    if(ImGui::TreeNode("Transform")){
        RenderPosition(movable_object);
        RenderRotation(movable_object);
        RenderScale(movable_object);
        RenderDirection(movable_object);
        ImGui::TreePop();
    }
}

void MovableObjectView::RenderPosition(
        std::shared_ptr<MovableObject> movable_object){
    static float raw[3];
    const glm::vec3& position = movable_object->getPosition();
    raw[0] = position.x;
    raw[1] = position.y;
    raw[2] = position.z;

    ImGui::SliderFloat3("Position", raw, -2, 2);
    movable_object->moveTo(glm::vec3(raw[0], raw[1], raw[2]));
}

void MovableObjectView::RenderRotation(
        std::shared_ptr<MovableObject> movable_object){
    static float raw[3];
    const glm::vec3& rotation = movable_object->getRotation();
    raw[0] = rotation.x;
    raw[1] = rotation.y;
    raw[2] = rotation.z;

    ImGui::SliderFloat3("Rotation", raw, 0, 360);
    movable_object->rotateTo(glm::vec3(raw[0], raw[1], raw[2]));
}
void MovableObjectView::RenderScale(
        std::shared_ptr<MovableObject> movable_object){
    static float raw[3];
    const glm::vec3& scale = movable_object->getScale();
    raw[0] = scale.x;
    raw[1] = scale.y;
    raw[2] = scale.z;

    ImGui::SliderFloat3("Scale", raw, -5, 5);
    movable_object->scale(glm::vec3(raw[0], raw[1], raw[2]));
}

void MovableObjectView::RenderDirection(
        std::shared_ptr<MovableObject> movable_object){
    static float raw[3];
    const glm::vec3& v = movable_object->getDirection();
    raw[0] = v.x;
    raw[1] = v.y;
    raw[2] = v.z;

    ImGui::DragFloat3("Direction", raw, -5, 5);
}

}