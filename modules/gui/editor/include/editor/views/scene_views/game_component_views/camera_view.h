#ifndef PROJECT_CAMERA_VIEW_H
#define PROJECT_CAMERA_VIEW_H

#include <memory>

namespace ifx {

class CameraComponent;

class CameraView {
public:

    CameraView();
    ~CameraView();

    void Render(std::shared_ptr<CameraComponent> camera);
private:
};
}

#endif //PROJECT_CAMERA_VIEW_H