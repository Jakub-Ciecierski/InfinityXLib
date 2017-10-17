#ifndef PROJECT_SOFT_BODY_SCREEN_VIEW_H
#define PROJECT_SOFT_BODY_SCREEN_VIEW_H

#include <memory>
#include <math/math_ifx.h>

namespace ifx {

class CameraComponent;
class Renderer;
class RayCasting;
class RenderComponent;
class SoftBodyPicker;

class Mesh;

template<class T>
class SoftBodyFEMComponentBuilder;

class SoftBodyScreenView {
public:
    SoftBodyScreenView(std::shared_ptr<SoftBodyPicker> soft_body_picker);

    ~SoftBodyScreenView() = default;

    void SetCamera(std::shared_ptr<CameraComponent> camera) {
        camera_ = camera;
    }

    void Render(std::shared_ptr<Renderer> renderer,
                SoftBodyFEMComponentBuilder<double>* soft_body_builder);
private:
    void RenderImage(std::shared_ptr<Renderer> renderer);

    glm::vec2 ComputeLocalMousePosition();

    void Pick(
        SoftBodyFEMComponentBuilder<double>* soft_body_builder,
        const glm::vec2 &mouse_position);

    std::unique_ptr<Mesh> CreateLine(const glm::vec3 &p1,
                                     const glm::vec3 &p2);

    std::shared_ptr<CameraComponent> camera_;

    std::shared_ptr<SoftBodyPicker> picker_;

    float screen_width_;
    float screen_height_;

};
}
#endif //PROJECT_SOFT_BODY_SCREEN_VIEW_H
