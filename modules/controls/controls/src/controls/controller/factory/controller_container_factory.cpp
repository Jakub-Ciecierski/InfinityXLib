#include "controls/controller/factory/controller_container_factory.h"

#include <controls/controller/controller_container.h>
#include <controls/controller/controllers/factory/keyboard_controller_factory.h>
#include <controls/controller/controllers/factory/mouse_controller_factory.h>

namespace ifx {

ControllerContainerFactory::ControllerContainerFactory() {
    CreateDefaultFactories();
}

std::shared_ptr<ControllerContainer> ControllerContainerFactory::Create() {
    auto input_container = std::make_shared<ControllerContainer>(
        CreateMouseController(),
        CreateKeyboardController());

    return input_container;
}

ControllerContainerFactory &ControllerContainerFactory::SetMouseControllerFactory(
    std::shared_ptr<MouseControllerFactory> factory) {
    mouse_controller_factory_ = factory;
    return *this;
}

ControllerContainerFactory &ControllerContainerFactory::SetKeyboardControllerFactory(
    std::shared_ptr<KeyboardControllerFactory> factory) {
    keyboard_controller_factory_ = factory;
    return *this;
}

std::shared_ptr<MouseController> ControllerContainerFactory::CreateMouseController() {
    return mouse_controller_factory_->Create();
}

std::shared_ptr<KeyboardController>
ControllerContainerFactory::CreateKeyboardController() {
    return keyboard_controller_factory_->Create();
}

void ControllerContainerFactory::CreateDefaultFactories() {
    keyboard_controller_factory_ =
        std::make_shared<KeyboardControllerFactory>();
    mouse_controller_factory_ = std::make_shared<MouseControllerFactory>();
}

}