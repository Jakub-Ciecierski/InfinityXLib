#ifndef PROJECT_KEYBOARD_INPUT_EVENT_H
#define PROJECT_KEYBOARD_INPUT_EVENT_H

#include <controls/controller/controller_event.h>

#include <controls/controller/controller_types.h>

namespace ifx {

class KeyboardControllerEvent : public ControllerEvent {
public:
    KeyboardControllerEvent(const KeyboardControllerKeyType&& type);

    ~KeyboardControllerEvent();

    const KeyboardControllerKeyType& type(){return type_;}

private:
    KeyboardControllerKeyType type_;

};
}


#endif //PROJECT_KEYBOARD_INPUT_EVENT_H
