#include "controls/controller/events/mouse_controller_event.h"

namespace ifx {

MouseControllerEvent::MouseControllerEvent(
    const MouseControllerKeyType &&type) :
    type_(type) {}

MouseControllerEvent::~MouseControllerEvent() {}

}