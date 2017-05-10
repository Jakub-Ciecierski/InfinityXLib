#include "controls/controller/controllers/keyboard_controller.h"

#include <controls/controller/events/keyboard_controller_event.h>

namespace ifx {

KeyboardController::KeyboardController(KeyboardEvents input_events) {
    for(auto& event : input_events){
        events_.push_back(event);
    }
}

KeyboardController::~KeyboardController(){}

std::shared_ptr<KeyboardControllerEvent> KeyboardController::GetEvent(
        KeyboardControllerKeyType type){
    for(auto& input : events_){
        auto key_input
                = std::static_pointer_cast<KeyboardControllerEvent>(input);
        if(key_input->type() == type)
            return key_input;
    }
    return nullptr;
}

}