#include "controls/command/commands/keyboard_command.h"

#include <controls/controller/events/keyboard_controller_event.h>

namespace ifx {

KeyboardCommand::KeyboardCommand(const CommandExecutable &&executable,
                                 const KeyboardCommandCondition &&condition) :
    Command(std::move(executable)),
    condition_(condition) {}

KeyboardCommand::~KeyboardCommand() {}

bool KeyboardCommand::IsConditionSatisfied() {
    switch (condition_.type_) {
        case KeyboardControllerCallbackType::PRESSED:
            return condition_.event_->IsPressed();
        case KeyboardControllerCallbackType::RELEASED:
            return condition_.event_->IsReleased();
        case KeyboardControllerCallbackType::UNKNOWN:return false;
    }
    return false;
}

}