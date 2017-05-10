#include "controls/controller/controller_event.h"

namespace ifx {

ControllerEvent::ControllerEvent() :
        is_pressed_(false),
        is_released_(false){}

ControllerEvent::~ControllerEvent(){}

bool ControllerEvent::IsPressed(){
    return is_pressed_;
}

bool ControllerEvent::IsReleased(){
    return is_released_;
}

void ControllerEvent::Reset(){
    is_released_ = false;
}

void ControllerEvent::OnPressed(){
    is_pressed_ = true;
    is_released_ = false;
}

void ControllerEvent::OnReleased(){
    is_pressed_ = false;
    is_released_ = true;
}

}