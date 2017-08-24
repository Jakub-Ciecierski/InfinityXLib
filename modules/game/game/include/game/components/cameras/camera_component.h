#ifndef PROJECT_CAMERACOMPONENT_H
#define PROJECT_CAMERACOMPONENT_H

#include <graphics/rendering/camera/camera.h>
#include <game/game_component.h>

namespace ifx {

class CameraComponent : public GameComponent, public Camera {
public:

    CameraComponent(int *width, int *height,
                    float FOV = 45.0f,
                    float near = 0.01f, float far = 100.0f);

    ~CameraComponent() = default;

private:
};
}

#endif //PROJECT_CAMERACOMPONENT_H
