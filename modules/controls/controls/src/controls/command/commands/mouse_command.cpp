#include <controller/events/mouse_scroll_controller_event.h>
#include "controls/command/commands/mouse_command.h"

#include "controls/controller/events/mouse_controller_event.h"

namespace ifx {

MouseCommand::MouseCommand(const CommandExecutable&& executable,
                           const MouseCommandCondition&& mouse_condition) :
        Command(std::move(executable)),
        condition_(mouse_condition){}

MouseCommand::~MouseCommand(){}

bool MouseCommand::IsConditionSatisfied(){
    switch(condition_.type_){
        case MouseControllerCallbackType::PRESSED:
            return condition_.event_->IsPressed();
        case MouseControllerCallbackType::RELEASED:
            return condition_.event_->IsReleased();
        case MouseControllerCallbackType::SCROLL_ACTIVE:
            return std::static_pointer_cast<MouseScrollControllerEvent>(
                    condition_.event_)->IsActivated();
        case MouseControllerCallbackType::UNKNOWN:
            return false;
    }
}

}