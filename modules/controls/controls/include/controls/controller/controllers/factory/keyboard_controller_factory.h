#ifndef PROJECT_KEYBOARD_INPUT_FACTORY_H
#define PROJECT_KEYBOARD_INPUT_FACTORY_H

#include <memory>

namespace ifx {

class KeyboardController;

class KeyboardControllerFactory {
public:
    KeyboardControllerFactory();
    ~KeyboardControllerFactory();

    std::shared_ptr<KeyboardController> Create();

private:
};
}

#endif //PROJECT_KEYBOARD_INPUT_FACTORY_H
