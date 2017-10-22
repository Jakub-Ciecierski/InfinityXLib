#ifndef PROJECT_SOFT_BODY_PICKER_H
#define PROJECT_SOFT_BODY_PICKER_H

#include <vector>
#include <memory>

#include <math/math_ifx.h>

#include <RTFEM/FEM/Meshing/TriangleMesh.h>
#include <RTFEM/FEM/Vertex.h>

#include <game/components/physics/builder/soft_body_fem_component_builder.h>

struct Vertex;

class VBO;

namespace ifx {

struct Ray;

class RenderComponent;
class RayCasting;
class BoxCasting;
class CameraComponent;
class SoftBodyNodeSelection;

class SoftBodyPicker {
public:
    SoftBodyPicker(std::unique_ptr<RayCasting> ray_casting,
                   std::unique_ptr<BoxCasting> box_casting,
                   std::unique_ptr<SoftBodyNodeSelection> node_selection,
                   std::unique_ptr<SoftBodyNodeSelection> face_selection);
    ~SoftBodyPicker() = default;

    std::shared_ptr<RenderComponent> current_picked(){return current_picked_;}

    const SoftBodyNodeSelection& node_selection() const {
        return *node_selection_;
    }
    const SoftBodyNodeSelection& face_selection() const {
        return *face_selection_;
    }

    float window_width(){return window_width_;}
    float window_height(){return window_height_;}

    const glm::vec2& last_mouse_position(){return last_mouse_position_;}

    void Pick(SoftBodyFEMComponentBuilder<double>* soft_body_builder,
              std::shared_ptr<CameraComponent> camera,
              float window_width,
              float window_height,
              const glm::vec2 &viewport_space);

    void EnableBoxCasting();
    void DisableBoxCasting();

private:
    bool CheckViewportCorrectness(
        float window_width, float window_height,
        const glm::vec2 &viewport_space);
    bool CheckCorrectness(std::shared_ptr<RenderComponent> render_component);

    void RayCastingPick(
        SoftBodyFEMComponentBuilder<double>* soft_body_builder,
        std::shared_ptr<CameraComponent> camera,
        float window_width,
        float window_height,
        const glm::vec2 &viewport_space);
    Ray UpdateRayCasting(std::shared_ptr<CameraComponent> camera,
                         float window_width,
                         float window_height,
                         const glm::vec2 &viewport_space);
    int ComputeRayIntersection(
        const glm::mat4 &model_matrix,
        const std::vector<Vertex> &vertices,
        const Ray &ray);
    void ComputeTriangleRayIntersection(
        const glm::mat4 &model_matrix,
        const std::vector<rtfem::TriangleFace>& triangle_faces,
        const std::vector<std::shared_ptr<rtfem::Vertex<double>>>& vertices,
        const Ray &ray);

    void BoxCastingPick(
        std::shared_ptr<RenderComponent> render_component,
        std::shared_ptr<CameraComponent> camera,
        float window_width,
        float window_height,
        const glm::vec2 &viewport_space);
    void UpdateBoxCasting(std::shared_ptr<CameraComponent> camera,
                          float window_width,
                          float window_height);
    void ComputeBoxIntersection(
        std::shared_ptr<RenderComponent> render_component,
        std::shared_ptr<CameraComponent> camera,
        float window_width,
        float window_height);

    /**
     * TODO. Currently colored vertices are flickering with old and new color
     * @param vbo
     */
    void ColorSelectedVertices(
        VBO& vbo);

    void ColorSelectedFaces(
        VBO& vbo,
        const std::vector<rtfem::TriangleFace>& triangle_faces);

    std::shared_ptr<RenderComponent> current_picked_;

    std::unique_ptr<RayCasting> ray_casting_;
    std::unique_ptr<BoxCasting> box_casting_;

    std::unique_ptr<SoftBodyNodeSelection> node_selection_;
    std::unique_ptr<SoftBodyNodeSelection> face_selection_;

    const float SPHERE_RADIUS = 0.1f;

    float window_width_;
    float window_height_;

    glm::vec2 last_mouse_position_;

    bool is_box_casting_enabled_;
};

}

#endif //PROJECT_SOFT_BODY_PICKER_H
