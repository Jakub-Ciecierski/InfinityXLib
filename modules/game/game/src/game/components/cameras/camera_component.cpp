#include "game/components/cameras/camera_component.h"

namespace ifx{
CameraComponent::CameraComponent(int *width, int *height,
                                 float FOV,
                                 float near, float far) :
    GameComponent(GameComponentType::CAMERA),
    Camera(width, height, FOV, near, far){}

}