#include "editor/views/soft_body_views/picking/soft_body_picker.h"

#include "editor/views/soft_body_views/picking/ray_casting.h"
#include "editor/views/soft_body_views/picking/box_casting.h"
#include <editor/views/soft_body_views/picking/soft_body_node_selection.h>

#include <graphics/shaders/data/shader_data.h>
#include <graphics/model/model.h>
#include <graphics/model/mesh.h>

#include <game/components/cameras/camera_component.h>
#include <game/components/render/render_component.h>
#include "game/components/physics/soft_body_fem_component.h"

#include <common/unique_ptr.h>

#include <gui/imgui/imgui.h>

#include <RTFEM/FEM/Meshing/Intersections.h>

#include <math/print_math.h>

#include "physics/soft_body/soft_body_fem.h"

namespace ifx {

SoftBodyPicker::SoftBodyPicker(
    std::unique_ptr<RayCasting> ray_casting,
    std::unique_ptr<BoxCasting> box_casting,
    std::unique_ptr<SoftBodyNodeSelection> node_selection,
    std::unique_ptr<SoftBodyNodeSelection> face_selection) :
    current_picked_(nullptr),
    ray_casting_(std::move(ray_casting)),
    box_casting_(std::move(box_casting)),
    node_selection_(std::move(node_selection)),
    face_selection_(std::move(face_selection)),
    window_width_(0),
    window_height_(0),
    last_mouse_position_(glm::vec2(0,0)),
    is_box_casting_enabled_(true){}

void SoftBodyPicker::Pick(SoftBodyFEMComponentBuilder<double>* soft_body_builder,
                          std::shared_ptr<CameraComponent> camera,
                          float window_width,
                          float window_height,
                          const glm::vec2 &viewport_space) {
    window_width_ = window_width;
    window_height_ = window_height;
    last_mouse_position_ = viewport_space;
    if(!CheckViewportCorrectness(window_width, window_height, viewport_space)){
        box_casting_->Finish();
        face_selection_->Reset();
        return;
    }
    if(!CheckCorrectness(soft_body_builder->fem_render())) {
        return;
    }
    if(is_box_casting_enabled_){
        BoxCastingPick(soft_body_builder->fem_render(),
                       camera,
                       window_width,
                       window_height,
                       viewport_space);
    }

    RayCastingPick(soft_body_builder,
                   camera,
                   window_width,
                   window_height,
                   viewport_space);

    ColorSelectedVertices(*(soft_body_builder->fem_render()->
        models()[0]->getMesh(0)->vbo()));
    ColorSelectedFaces(*(soft_body_builder->fem_render()->
                           models()[0]->getMesh(0)->vbo()),
                       soft_body_builder->GetFEMGeometry().triangle_faces);

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
    SoftBodyFEMComponentBuilder<double>* soft_body_builder,
    std::shared_ptr<CameraComponent> camera,
    float window_width,
    float window_height,
    const glm::vec2 &viewport_space){
    auto ray = UpdateRayCasting(camera, window_width, window_height,
                                viewport_space);

    if(node_selection_->IsInputRayCasting()){
        ComputeRayIntersection(
            soft_body_builder->fem_render()->GetModelMatrix(),
            soft_body_builder->fem_render()->models()[0]->getMesh(0)->vertices(),
            ray);
    }

    if(face_selection_->IsInputRayCasting()){
        ComputeTriangleRayIntersection(
            soft_body_builder,
            soft_body_builder->fem_render()->GetModelMatrix(),
            soft_body_builder->GetFEMGeometry().triangle_faces,
            soft_body_builder->GetFEMGeometry().vertices,
            ray);
    }

}

Ray SoftBodyPicker::UpdateRayCasting(std::shared_ptr<CameraComponent> camera,
                                      float window_width,
                                      float window_height,
                                      const glm::vec2 &viewport_space) {
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

    return ray_casting_->ComputeRay(viewport_space);
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

    if(intersection_count < 1 && !node_selection_->IsInputShiftModifier()){
        node_selection_->Reset();
    }

    return intersection_count;
}

void SoftBodyPicker::ComputeTriangleRayIntersection(
    SoftBodyFEMComponentBuilder<double>* soft_body_builder,
    const glm::mat4 &model_matrix,
    const std::vector<rtfem::TriangleFace<double>>& triangle_faces,
    const std::vector<std::shared_ptr<rtfem::Vertex<double>>>& vertices,
    const Ray &ray){
    int index = 0;
    std::vector<TriangleRayIntersectionOutput> correct_intersection_outputs;

    int closest_index = -1;
    float closest_distance = 9999;
    Triangle closest_triangle;

    const rtfem::FEMSolverOutput<double>* fem_solver_output = nullptr;
    if(soft_body_builder->last_soft_body_fem_component()){
        fem_solver_output = soft_body_builder->last_soft_body_fem_component()
            ->last_fem_solver_output();
    }
    try{
    for (const auto &triangle_face : triangle_faces) {
        if(!triangle_face.is_boundary_face){
            index++;
            continue;
        }
        auto rtfem_vertex1 = vertices[triangle_face.v1];
        auto rtfem_vertex2 = vertices[triangle_face.v2];
        auto rtfem_vertex3 = vertices[triangle_face.v3];

        auto glm_vertex1_4 = glm::vec4(glm::vec3(
            rtfem_vertex1->x(), rtfem_vertex1->y(), rtfem_vertex1->z()), 1);
        auto glm_vertex2_4 = glm::vec4(glm::vec3(
            rtfem_vertex2->x(), rtfem_vertex2->y(), rtfem_vertex2->z()), 1);
        auto glm_vertex3_4 = glm::vec4(glm::vec3(
            rtfem_vertex3->x(), rtfem_vertex3->y(), rtfem_vertex3->z()), 1);

        // Apply current displacements;
        if(fem_solver_output){
            auto size = fem_solver_output->displacement.size();

            auto index = triangle_face.v1*3 + 0;
            if(index < size){
                glm_vertex1_4[0] +=
                        fem_solver_output->displacement[index];
            }

            index = triangle_face.v1*3 + 1;
            if(index < size){
                glm_vertex1_4[1] +=
                        fem_solver_output->displacement[triangle_face.v1*3 + 1];
            }

            index = triangle_face.v1*3 + 2;
            if(index < size){
                glm_vertex1_4[2] +=
                        fem_solver_output->displacement[triangle_face.v1*3 + 2];
            }

            index = triangle_face.v2*3 + 0;
            if(index < size){
                glm_vertex2_4[0] +=
                        fem_solver_output->displacement[triangle_face.v2*3 + 0];
            }

            index = triangle_face.v2*3 + 1;
            if(index < size){
                glm_vertex2_4[1] +=
                        fem_solver_output->displacement[triangle_face.v2*3 + 1];
            }

            index = triangle_face.v2*3 + 2;
            if(index < size){
                glm_vertex2_4[2] +=
                        fem_solver_output->displacement[triangle_face.v2*3 + 2];
            }


            index = triangle_face.v3*3 + 0;
            if(index < size){
                glm_vertex3_4[0] +=
                        fem_solver_output->displacement[triangle_face.v3*3 + 0];
            }

            index = triangle_face.v3*3 + 1;
            if(index < size){
                glm_vertex3_4[1] +=
                        fem_solver_output->displacement[triangle_face.v3*3 + 1];
            }

            index = triangle_face.v3*3 + 2;
            if(index < size){
                glm_vertex3_4[2] +=
                        fem_solver_output->displacement[triangle_face.v3*3 + 2];
            }
        }

        auto glm_world_vertex1 = glm::vec3(model_matrix * glm_vertex1_4);
        auto glm_world_vertex2 = glm::vec3(model_matrix * glm_vertex2_4);
        auto glm_world_vertex3 = glm::vec3(model_matrix * glm_vertex3_4);
        auto triangle = Triangle{
            glm_world_vertex1,
            glm_world_vertex2,
            glm_world_vertex3};
        auto output = ray_casting_->TriangleRayIntersection(ray, triangle);
        if(output.is_intersection){
            auto distance
                = glm::distance(output.intersection_point, ray.origin);
            if(distance < closest_distance){
                closest_distance = distance;
                closest_index = index;
                closest_triangle = triangle;
            }
        }

        index++;
    }
    if(closest_index != -1){
        face_selection_->NotifyIntersection(closest_index, SelectionType::Ray);

    }else{
        face_selection_->Reset();
    }
    }catch(const std::exception& e){
        face_selection_->Reset();
    }

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
    const auto selected_color = 10.0f;
    const auto not_selected_color = 0.0f;

    bool value_changed = false;

    std::vector<Vertex> *vertices = vbo.vertices();
    for(unsigned i = 0; i < vertices->size(); i++){
        auto& vertex = (*vertices)[i];
        if(node_selection_->IsSelected(i)){
            if(vertex.TexCoords.x != selected_color){
                value_changed = true;
            }
            vertex.TexCoords.x = selected_color;
        }else{
            if(vertex.TexCoords.x != not_selected_color){
                value_changed = true;
            }
            vertex.TexCoords.x = not_selected_color;
        }
    }
    if(value_changed)
        vbo.Update();
}

void SoftBodyPicker::ColorSelectedFaces(
    VBO& vbo,
    const std::vector<rtfem::TriangleFace<double>>& triangle_faces){
    const auto selected_color = 10.0f;
    const auto not_selected_color = 0.0f;

    auto* vertices = vbo.vertices();

    for(unsigned int i = 0; i < triangle_faces.size(); i++){
        (*vertices)[triangle_faces[i].v1].TexCoords.y = not_selected_color;
        (*vertices)[triangle_faces[i].v2].TexCoords.y = not_selected_color;
        (*vertices)[triangle_faces[i].v3].TexCoords.y = not_selected_color;
    }
    for(unsigned int i = 0; i < triangle_faces.size(); i++){
        if(face_selection_->IsSelected(i)){
            (*vertices)[triangle_faces[i].v1].TexCoords.y = selected_color;
            (*vertices)[triangle_faces[i].v2].TexCoords.y = selected_color;
            (*vertices)[triangle_faces[i].v3].TexCoords.y = selected_color;
        }
    }
    vbo.Update();
}

void SoftBodyPicker::EnableBoxCasting(){
    is_box_casting_enabled_ = true;
}

void SoftBodyPicker::DisableBoxCasting(){
    is_box_casting_enabled_ = false;
}


}