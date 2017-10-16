#ifndef PROJECT_SOFT_BODY_PICKER_H
#define PROJECT_SOFT_BODY_PICKER_H

#include <vector>
#include <memory>

#include <math/math_ifx.h>

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
                   std::unique_ptr<SoftBodyNodeSelection> node_selection);
    ~SoftBodyPicker() = default;

    std::shared_ptr<RenderComponent> current_picked(){return current_picked_;}

    const SoftBodyNodeSelection& node_selection() const {
        return *node_selection_;
    }

    void Pick(std::shared_ptr<RenderComponent> render_component,
              std::shared_ptr<CameraComponent> camera,
              float window_width,
              float window_height,
              const glm::vec2 &viewport_space);
private:
    bool CheckViewportCorrectness(
        float window_width, float window_height,
        const glm::vec2 &viewport_space);
    bool CheckCorrectness(std::shared_ptr<RenderComponent> render_component);

    void RayCastingPick(
        std::shared_ptr<RenderComponent> render_component,
        std::shared_ptr<CameraComponent> camera,
        float window_width,
        float window_height,
        const glm::vec2 &viewport_space);
    void UpdateRayCasting(std::shared_ptr<CameraComponent> camera,
                          float window_width,
                          float window_height);
    int ComputeRayIntersection(
        const glm::mat4 &model_matrix,
        const std::vector<Vertex> &vertices,
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

    std::shared_ptr<RenderComponent> current_picked_;

    std::unique_ptr<RayCasting> ray_casting_;
    std::unique_ptr<BoxCasting> box_casting_;

    std::unique_ptr<SoftBodyNodeSelection> node_selection_;

    const float SPHERE_RADIUS = 0.1f;
};

}

#endif //PROJECT_SOFT_BODY_PICKER_H
