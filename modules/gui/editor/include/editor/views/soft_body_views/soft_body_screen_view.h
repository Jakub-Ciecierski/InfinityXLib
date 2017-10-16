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

class SoftBodyScreenView {
public:
    SoftBodyScreenView(std::shared_ptr<SoftBodyPicker> soft_body_picker);

    ~SoftBodyScreenView() = default;

    void SetCamera(std::shared_ptr<CameraComponent> camera) {
        camera_ = camera;
    }

    void Render(std::shared_ptr<Renderer> renderer,
                std::shared_ptr<RenderComponent> render_component);
private:
    std::unique_ptr<Mesh> CreateLine(const glm::vec3 &p1,
                                     const glm::vec3 &p2);

    std::shared_ptr<CameraComponent> camera_;

    std::shared_ptr<SoftBodyPicker> picker_;

};
}
#endif //PROJECT_SOFT_BODY_SCREEN_VIEW_H
