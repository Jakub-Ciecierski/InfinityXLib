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
class CameraComponent;

class SoftBodyPicker {
public:
    SoftBodyPicker();
    ~SoftBodyPicker() = default;

    const std::vector<unsigned int>& selected_vertices(){
        return selected_vertices_;
    }

    std::shared_ptr<RenderComponent> current_picked(){return current_picked_;}

    void Pick(std::shared_ptr<RenderComponent> render_component,
              std::shared_ptr<CameraComponent> camera,
              float window_width,
              float window_height,
              const glm::vec2 &viewport_space);

    void Reset();
private:
    bool CheckCorrectness(std::shared_ptr<RenderComponent> render_component);
    void UpdateRayCasting(std::shared_ptr<CameraComponent> camera,
                          float window_width,
                          float window_height);
    void ComputeIntersection(
        const glm::mat4 &model_matrix,
        const std::vector<Vertex> &vertices,
        const Ray &ray);
    void ColorSelectedVertices(
        VBO& vbo);

    std::shared_ptr<RenderComponent> current_picked_;

    std::vector<unsigned int> selected_vertices_;

    std::unique_ptr<RayCasting> ray_casting_;

    const float SPHERE_RADIUS = 0.1f;
};

}

#endif //PROJECT_SOFT_BODY_PICKER_H
