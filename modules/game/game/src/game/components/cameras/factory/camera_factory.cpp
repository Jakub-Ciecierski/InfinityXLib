#include <game/components/cameras/camera_component.h>

#include "game/components/cameras/factory/camera_factory.h"
#include <graphics/rendering/window/window.h>

namespace ifx{

CameraFactory::CameraFactory(){}

CameraFactory::~CameraFactory(){}

std::shared_ptr<CameraComponent> CameraFactory::CreateCamera(Window* window){
    auto camera = std::shared_ptr<CameraComponent>(
            new ifx::CameraComponent(window->width(), window->height()));
    return camera;
}
}