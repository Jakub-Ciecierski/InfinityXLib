#include "editor/views/soft_body_views/picking/soft_body_picker.h"

#include "editor/views/soft_body_views/picking/ray_casting.h"
#include "editor/views/soft_body_views/picking/box_casting.h"
#include <editor/views/soft_body_views/picking/soft_body_node_selection.h>

#include <graphics/shaders/data/shader_data.h>
#include <graphics/model/model.h>
#include <graphics/model/mesh.h>

#include <game/components/cameras/camera_component.h>
#include <game/components/render/render_component.h>

#include <common/unique_ptr.h>

#include <gui/imgui/imgui.h>

namespace ifx {

SoftBodyPicker::SoftBodyPicker(
    std::unique_ptr<RayCasting> ray_casting,
    std::unique_ptr<BoxCasting> box_casting,
    std::unique_ptr<SoftBodyNodeSelection> node_selection) :
    current_picked_(nullptr),
    ray_casting_(std::move(ray_casting)),
    box_casting_(std::move(box_casting)),
    node_selection_(std::move(node_selection)) {
}

void SoftBodyPicker::Pick(std::shared_ptr<RenderComponent> render_component,
                          std::shared_ptr<CameraComponent> camera,
                          float window_width,
                          float window_height,
                          const glm::vec2 &viewport_space) {
    if(!CheckViewportCorrectness(window_width, window_height, viewport_space)){
        box_casting_->Finish();
        return;
    }
    if(!CheckCorrectness(render_component)) {
        return;
    }
    BoxCastingPick(render_component,
                   camera,
                   window_width,
                   window_height,
                   viewport_space);
    RayCastingPick(render_component,
                   camera,
                   window_width,
                   window_height,
                   viewport_space);


    ColorSelectedVertices(*(render_component->models()[0]->getMesh(0)->vbo()));
}

bool SoftBodyPicker::CheckViewportCorrectness(
    float window_width,
    float window_height,
    const glm::vec2 &viewport_space) {
    return (viewport_space.x >= 0
        && viewport_space.y >= 0
        && viewport_space.x < window_width
        && viewport_space.y < window_height);
}

bool SoftBodyPicker::CheckCorrectness(
    std::shared_ptr<RenderComponent> render_component){
    if(render_component != current_picked_){
        node_selection_->Reset();
    }
    if (!render_component)
        return false;
    if (render_component->models().size() < 1) {
        return false;
    }
    current_picked_ = render_component;

    return true;
}

void SoftBodyPicker::RayCastingPick(
    std::shared_ptr<RenderComponent> render_component,
    std::shared_ptr<CameraComponent> camera,
    float window_width,
    float window_height,
    const glm::vec2 &viewport_space){
    if(!node_selection_->IsInputRayCasting())
        return;

    UpdateRayCasting(camera, window_width, window_height);
    auto ray = ray_casting_->ComputeRay(viewport_space);

    auto mesh = render_component->models()[0]->getMesh(0);
    auto intersection_count =
        ComputeRayIntersection(render_component->GetModelMatrix(),
                               mesh->vertices(),
                               ray);
    if(intersection_count < 1 && !node_selection_->IsInputShiftModifier()){
        node_selection_->Reset();
    }
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

int SoftBodyPicker::ComputeRayIntersection(
    const glm::mat4 &model_matrix,
    const std::vector<Vertex> &vertices,
    const Ray &ray){
    int index = 0;
    int intersection_count = 0;
    for (const auto &vertex : vertices) {
        auto vertex4 = glm::vec4(vertex.Position, 1);
        auto world_vertex = glm::vec3(model_matrix * vertex4);

        auto intesection_output = ray_casting_->RaySphereIntersection(
            ray, Sphere{world_vertex, SPHERE_RADIUS});
        if (intesection_output.number_of_solutions > 0) {
            node_selection_->NotifyIntersection(index, SelectionType::Ray);
            intersection_count++;
        }
        index++;
    }
    return intersection_count;
}

void SoftBodyPicker::BoxCastingPick(
    std::shared_ptr<RenderComponent> render_component,
    std::shared_ptr<CameraComponent> camera,
    float window_width,
    float window_height,
    const glm::vec2 &viewport_space){
    if(node_selection_->IsInputBeginBoxCasting()){
        box_casting_->Begin(viewport_space);
    }
    if(node_selection_->IsInputUpdateBoxCasting()) {
        UpdateBoxCasting(camera, window_width, window_height);
        box_casting_->SetEndViewport(viewport_space);
        std::cout << "Area: " << box_casting_->box_viewport().Area() <<
                                                                     std::endl;
        if(!node_selection_->IsInputShiftModifier()
            && box_casting_->box_viewport().Area() > 0.1f){
            node_selection_->Reset();
        }

        ComputeBoxIntersection(render_component, camera,
                               window_width, window_height);
    }
    if(node_selection_->IsInputEndBoxCasting()){
        box_casting_->Finish();
    }
}

void SoftBodyPicker::ComputeBoxIntersection(
    std::shared_ptr<RenderComponent> render_component,
    std::shared_ptr<CameraComponent> camera,
    float window_width,
    float window_height) {
    const auto& model_matrix = render_component->GetModelMatrix();
    const auto& view_matirx = camera->getViewMatrix();
    const auto& projection_matrix = camera->getProjectionMatrix();
    auto MVP = projection_matrix * view_matirx * model_matrix;

    const auto& box_viewport = box_casting_->box_viewport();

    const auto& vertices
        = render_component->models()[0]->getMesh(0)->vertices();
    for(unsigned int i = 0; i < vertices.size(); i++){
        auto vertex_4 = glm::vec4(vertices[i].Position, 1.0f);
        auto clip = MVP * vertex_4;
        auto nds = clip / clip.w;
        auto viewport = glm::vec2(
            ((nds.x * 0.5f) + 0.5f) * window_width,
            ((nds.y * 0.5f) + 0.5f) * window_height
        );
        if(box_viewport.IsInside(viewport)){
            node_selection_->NotifyIntersection(i, SelectionType::Box);
        }
    };

}

void SoftBodyPicker::UpdateBoxCasting(std::shared_ptr<CameraComponent> camera,
                                      float window_width,
                                      float window_height) {
    box_casting_->projection(camera->getProjectionMatrix());
    box_casting_->view(camera->getViewMatrix());
    box_casting_->window_width(window_width);
    box_casting_->window_height(window_height);
}

void SoftBodyPicker::ColorSelectedVertices(
    VBO& vbo){
    const auto selected_color = glm::vec2(10, 10);
    const auto not_selected_color = glm::vec2(0, 0);

    bool value_changed = false;

    std::vector<Vertex> *vertices = vbo.vertices();
    for(unsigned i = 0; i < vertices->size(); i++){
        auto& vertex = (*vertices)[i];
        if(node_selection_->IsSelected(i)){
            if(vertex.TexCoords != selected_color){
                value_changed = true;
            }
            vertex.TexCoords = selected_color;
        }else{
            if(vertex.TexCoords != not_selected_color){
                value_changed = true;
            }
            vertex.TexCoords = not_selected_color;
        }
    }
    if(value_changed)
        vbo.Update();
}

}