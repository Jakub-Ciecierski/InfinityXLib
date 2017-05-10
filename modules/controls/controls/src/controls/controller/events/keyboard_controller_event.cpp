#include "controls/controller/events/keyboard_controller_event.h"

namespace ifx {

KeyboardControllerEvent::KeyboardControllerEvent(
        const KeyboardControllerKeyType&& type) :
        type_(type){}

KeyboardControllerEvent::~KeyboardControllerEvent(){}

}