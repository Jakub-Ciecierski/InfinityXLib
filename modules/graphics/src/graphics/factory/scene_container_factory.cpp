#include "graphics/factory/scene_factory.h"

#include <graphics/rendering/camera/camera.h>
#include <graphics/rendering/window/window.h>

namespace ifx {

SceneFactory::SceneFactory() {}
SceneFactory::~SceneFactory() {}

std::shared_ptr<Camera> SceneFactory::CreateCamera(ifx::Window *window) {
    auto camera
        = std::shared_ptr<ifx::Camera>(new ifx::Camera(window->width(),
                                                       window->height()));
    return camera;
}

}