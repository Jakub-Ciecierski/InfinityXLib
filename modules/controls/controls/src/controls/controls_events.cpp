#include <iostream>
#include "controls/controls_events.h"

namespace ifx {

ControlsEvents::ControlsEvents() {
    mouse_events_.LeftMouse = new MouseEvent(MouseButtonType::BUTTON_LEFT);
    mouse_events_.RightMouse = new MouseEvent(MouseButtonType::BUTTON_RIGHT);
    mouse_events_.MiddleMouse = new MouseEvent(MouseButtonType::BUTTON_MIDDLE);

    keyboard_keys_.resize(1024);
}

ControlsEvents::~ControlsEvents() {
}

ControlsEvents& ControlsEvents::GetInstance(){
    static ControlsEvents controls;
    return controls;
}

void ControlsEvents::OnKeyboardEvent(int action, int key){
    if (key >= 0 && key < (int)keyboard_keys_.size()) {
        if (action == GLFW_PRESS) {
            keyboard_keys_[key] = true;
        } else if (action == GLFW_RELEASE) {
            keyboard_keys_[key] = false;
        }
    }
}

void ControlsEvents::OnMouseButtonEvent(MouseButtonType type, bool is_pressed,
                                  float xpos, float ypos) {
    MouseEvent* current_event = nullptr;
    if (mouse_events_.LeftMouse->type() == type)
        current_event = mouse_events_.LeftMouse;
    if (mouse_events_.RightMouse->type() == type)
        current_event = mouse_events_.RightMouse;
    if (mouse_events_.MiddleMouse->type() == type)
        current_event = mouse_events_.MiddleMouse;

    if(current_event == nullptr)
        return;

    current_event->is_pressed(is_pressed);
    current_event->x(xpos);
    current_event->y(ypos);
}

void ControlsEvents::OnMouseEvent(float xpos, float ypos){
    mouse_events_.pos_x = xpos;
    mouse_events_.pos_y = ypos;
}

void ControlsEvents::OnMouseScrollEvent(float xoffset, float yoffset){
    mouse_events_.scroll_x_offset = xoffset;
    mouse_events_.scroll_y_offset = yoffset;
}

void ControlsEvents::Update(){
    mouse_events_.prev_pos_x = mouse_events_.pos_x;
    mouse_events_.prev_pos_y = mouse_events_.pos_y;
}

}