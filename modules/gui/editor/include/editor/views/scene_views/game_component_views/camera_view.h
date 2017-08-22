#ifndef PROJECT_CAMERA_VIEW_H
#define PROJECT_CAMERA_VIEW_H

#include <memory>

namespace ifx {

class CameraComponent;

class CameraView {
public:

    CameraView() = default;
    ~CameraView() = default;

    void Render(std::shared_ptr<CameraComponent> camera);
private:
};
}

#endif //PROJECT_CAMERA_VIEW_H
