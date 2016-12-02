#include "engine_gui/views/scene_view.h"

#include <rendering/scene/scene.h>
#include <object/render_object.h>

#include <gui/imgui/imgui.h>
#include <gui/imgui/imgui_internal.h>

namespace ifx {

SceneView::SceneView(std::shared_ptr<Scene> scene) :
        scene_(scene),
        scene_listbox_item_current_(0){ }

SceneView::~SceneView(){ }

void SceneView::Render(){
    RenderWindow();
}

void SceneView::RenderWindow(){
    ImGui::SetNextWindowSize(ImVec2(350,600));
    ImGui::Begin("Scene");

    std::vector<std::shared_ptr<RenderObject>>& render_objects
            = scene_->render_objects();
    int size = render_objects.size();
    if(size != 0 ){
        display_names_.resize(size);
        for(unsigned int i = 0; i < size; i++){
            display_names_[i] = render_objects[i]->id().name().c_str();
        }
        ImGui::ListBox("Scene", &scene_listbox_item_current_,
                       display_names_.data(),
                       size,
                       std::min(size, 10));

        if(ImGui::CollapsingHeader("Selected Object"))
            RenderObjectInfo(render_objects[scene_listbox_item_current_]);
    }

    ImGui::End();
}

void SceneView::RenderObjectInfo(
        std::shared_ptr<RenderObject> render_object){
    ImGui::BulletText("Name: %s", render_object->id().name().c_str());
    if(ImGui::TreeNode("Transform")){
        RenderTransform(render_object);
        ImGui::TreePop();
    }
    if(ImGui::TreeNode("Properties")){
        RenderProperties(render_object);
        ImGui::TreePop();
    }
    if(ImGui::TreeNode("Components TODO")){
        ImGui::TreePop();
    }
}

void SceneView::RenderTransform(
        std::shared_ptr<RenderObject> render_object){
    RenderPosition(render_object);
    RenderRotation(render_object);
    RenderScale(render_object);
}

void SceneView::RenderPosition(
        std::shared_ptr<RenderObject> render_object){
    static float raw[3];
    const glm::vec3& position = render_object->getPosition();
    raw[0] = position.x;
    raw[1] = position.y;
    raw[2] = position.z;

    ImGui::SliderFloat3("Position", raw, -2, 2);
    render_object->moveTo(glm::vec3(raw[0], raw[1], raw[2]));
}

void SceneView::RenderRotation(
        std::shared_ptr<RenderObject> render_object){
    static float raw[3];
    const glm::vec3& rotation = render_object->getRotation();
    raw[0] = rotation.x;
    raw[1] = rotation.y;
    raw[2] = rotation.z;

    ImGui::SliderFloat3("Rotation", raw, 0, 360);
    render_object->rotateTo(glm::vec3(raw[0], raw[1], raw[2]));
}

void SceneView::RenderScale(std::shared_ptr<RenderObject> render_object){
    static float raw[3];
    const glm::vec3& scale = render_object->getScale();
    raw[0] = scale.x;
    raw[1] = scale.y;
    raw[2] = scale.z;

    ImGui::SliderFloat3("Scale", raw, -5, 5);
    render_object->scale(glm::vec3(raw[0], raw[1], raw[2]));
}

void SceneView::RenderProperties(
        std::shared_ptr<RenderObject> render_object){
    static bool do_render;
    do_render = render_object->do_render();
    ImGui::Checkbox("Do Render", &do_render);
    render_object->do_render(do_render);
}

} // namespace ifx
