#ifndef PROJECT_KEYBOARD_INPUT_H
#define PROJECT_KEYBOARD_INPUT_H

#include <controls/controller/controller.h>
#include <controls/controller/controller_types.h>

#include <vector>
#include <memory>

namespace ifx {

class KeyboardControllerEvent;

using KeyboardEvents = std::vector<std::shared_ptr<KeyboardControllerEvent>>;

class KeyboardController : public Controller {
public:

    KeyboardController(KeyboardEvents input_events);

    ~KeyboardController();

    std::shared_ptr<KeyboardControllerEvent> GetEvent(
            KeyboardControllerKeyType type);

private:

};

}


#endif //PROJECT_KEYBOARD_INPUT_H
