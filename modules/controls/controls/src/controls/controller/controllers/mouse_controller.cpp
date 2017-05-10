#include "controls/controller/controllers/mouse_controller.h"

#include "controls/controller/events/mouse_controller_event.h"
#include "controls/controller/events/mouse_scroll_controller_event.h"

namespace ifx {

MouseController::MouseController(const MouseControllerEvents&& mouse_input_events) :
        current_position_(MousePosition{0,0}),
        previous_position_(MousePosition{0,0}),
        scroll_offset_(MousePosition{0,0}){
    events_.push_back(mouse_input_events.left_button);
    events_.push_back(mouse_input_events.right_button);
    events_.push_back(mouse_input_events.middle_button);
    events_.push_back(mouse_input_events.scroll_input_event);
}

MouseController::~MouseController(){}

void MouseController::SetCurrentPosition(const MousePosition&& pos){
    current_position_ = pos;
}

void MouseController::SetScrollOffset(const MousePosition&& pos){
    scroll_offset_ = pos;
}

std::shared_ptr<MouseControllerEvent> MouseController::GetEvent(
        MouseControllerKeyType type){
    for(auto& input : events_){
        auto key_input
                = std::static_pointer_cast<MouseControllerEvent>(input);
        if(key_input->type() == type)
            return key_input;
    }
    return nullptr;
}

void MouseController::Update(float){
    Controller::Update();

    previous_position_ = current_position_;
}

}