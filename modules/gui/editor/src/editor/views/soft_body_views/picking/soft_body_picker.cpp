#include "editor/views/soft_body_views/picking/soft_body_picker.h"

#include "editor/views/soft_body_views/picking/ray_casting.h"

#include <graphics/shaders/data/shader_data.h>
#include <graphics/model/model.h>
#include <graphics/model/mesh.h>

#include <game/components/cameras/camera_component.h>
#include <game/components/render/render_component.h>

#include <common/unique_ptr.h>

namespace ifx {

SoftBodyPicker::SoftBodyPicker() : current_picked_(nullptr){
    ray_casting_ = ifx::make_unique<RayCasting>();
}

void SoftBodyPicker::Pick(std::shared_ptr<RenderComponent> render_component,
                          std::shared_ptr<CameraComponent> camera,
                          float window_width,
                          float window_height,
                          const glm::vec2 &viewport_space) {
    if(!CheckCorrectness(render_component)){
        return;
    }
    UpdateRayCasting(camera, window_width, window_height);

/*
    if(!ImGui::IsMouseClicked(1))
        return;*/
    auto ray = ray_casting_->ComputeRayDirection(viewport_space);
    ComputeIntersection(render_component->GetModelMatrix(),
                        render_component->models()[0]->getMesh(0)->vertices(),
                        ray);
}

void SoftBodyPicker::Reset(){
    selected_vertices_.clear();
}

bool SoftBodyPicker::CheckCorrectness(
    std::shared_ptr<RenderComponent> render_component){
    if(render_component != current_picked_){
        Reset();
    }
    if (!render_component)
        return false;
    if (render_component->models().size() < 1) {
        return false;
    }
    current_picked_ = render_component;

    return true;
}

void SoftBodyPicker::UpdateRayCasting(std::shared_ptr<CameraComponent> camera,
                                      float window_width,
                                      float window_height) {
    ray_casting_->projection(camera->getProjectionMatrix());
    ray_casting_->view(camera->getViewMatrix());
    if (camera->camera_style() == CameraStyle::ThirdPerson) {
        ray_casting_->origin(
            camera->getPosition() -
                glm::length(camera->getScale()) * camera->getDirection());
    } else {
        ray_casting_->origin(camera->getPosition());
    }

    ray_casting_->window_width(window_width);
    ray_casting_->window_height(window_height);
}

void SoftBodyPicker::ComputeIntersection(
    const glm::mat4& model_matrix,
    const std::vector<Vertex>& vertices,
    const Ray& ray){

    int index = 0;
    for (const auto &vertex : vertices) {
        auto vertex4 = glm::vec4(vertex.Position, 1);
        auto world_vertex = glm::vec3(model_matrix * vertex4);

        auto intesection_output = ray_casting_->RaySphereIntersection(
            ray, Sphere{world_vertex, SPHERE_RADIUS});
        if (intesection_output.number_of_solutions > 0) {
            selected_vertices_.push_back(index);
        }

        index++;
    }
}

}