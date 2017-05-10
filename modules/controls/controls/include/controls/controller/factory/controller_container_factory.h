#ifndef PROJECT_INPUT_EVENTS_CONTAINER_FACTORY_H
#define PROJECT_INPUT_EVENTS_CONTAINER_FACTORY_H

#include <memory>

namespace ifx {

class ControllerContainer;
class MouseController;
class KeyboardController;

class MouseControllerFactory;
class KeyboardControllerFactory;

class ControllerContainerFactory {
public:

    ControllerContainerFactory();
    ~ControllerContainerFactory();

    ControllerContainerFactory& SetMouseControllerFactory(
            std::shared_ptr<MouseControllerFactory> factory);

    ControllerContainerFactory& SetKeyboardControllerFactory(
            std::shared_ptr<KeyboardControllerFactory> factory);

    std::shared_ptr<ControllerContainer> Create();

private:
    void CreateDefaultFactories();

    std::shared_ptr<MouseController> CreateMouseController();
    std::shared_ptr<KeyboardController> CreateKeyboardController();

    std::shared_ptr<KeyboardControllerFactory> keyboard_controller_factory_;
    std::shared_ptr<MouseControllerFactory> mouse_controller_factory_;
};
}


#endif //PROJECT_INPUT_EVENTS_CONTAINER_FACTORY_H
