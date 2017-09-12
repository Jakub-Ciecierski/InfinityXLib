#ifndef PROJECT_CAMERA_FACTORY_H
#define PROJECT_CAMERA_FACTORY_H

namespace ifx {

class CameraComponent;
class Window;

class CameraFactory {
public:

    CameraFactory() = default;
    ~CameraFactory() = default;

    std::shared_ptr<CameraComponent> CreateCamera(Window *window);
private:
};
}

#endif //PROJECT_CAMERA_FACTORY_H
