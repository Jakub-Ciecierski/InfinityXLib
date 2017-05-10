#include "controls/controller/events/mouse_scroll_controller_event.h"

namespace ifx {

MouseScrollControllerEvent::MouseScrollControllerEvent() :
        MouseControllerEvent(MouseControllerKeyType::MOUSE_SCROLL),
        is_activated_(false){}

MouseScrollControllerEvent::~MouseScrollControllerEvent(){}

bool MouseScrollControllerEvent::IsPressed(){
    return false;
}

bool MouseScrollControllerEvent::IsReleased(){
    return false;
}

bool MouseScrollControllerEvent::IsActivated(){
    return is_activated_;
}

void MouseScrollControllerEvent::SetActivated(bool value){
    is_activated_ = value;
}

void MouseScrollControllerEvent::Reset(){
    // TODO, should be: MouseControllerEvent::Reset();
    ControllerEvent::Reset();

    is_activated_ = false;
}

}