#ifndef PROJECT_SOFT_BODY_SCREEN_VIEW_H
#define PROJECT_SOFT_BODY_SCREEN_VIEW_H

#include <memory>

namespace ifx {

class CameraComponent;
class Renderer;
class RayCasting;

class SoftBodyScreenView {
public:
    SoftBodyScreenView();

    ~SoftBodyScreenView() = default;

    void SetCamera(std::shared_ptr<CameraComponent> camera){
        camera_ = camera;
    }

    void Render(std::shared_ptr<Renderer> renderer);
private:
    std::shared_ptr<CameraComponent> camera_;

    std::unique_ptr<RayCasting> ray_casting_;
};

}

#endif //PROJECT_SOFT_BODY_SCREEN_VIEW_H
