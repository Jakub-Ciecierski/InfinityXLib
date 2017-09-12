#include "controls/controls.h"

#include <controls/command/command.h>
#include <controls/controls_container.h>
#include <controls/controller/events/keyboard_controller_event.h>
#include <controls/controller/events/mouse_controller_event.h>
#include <controls/controller/controller_container.h>
#include <controls/controller/controllers/keyboard_controller.h>
#include <controls/controller/controllers/mouse_controller.h>

namespace ifx {

Controls::Controls(
    std::shared_ptr<ControlContext> control_context,
    std::shared_ptr<ControllerContainer> input_container) :
    control_context_(control_context),
    controller_container_(input_container) {
    ControlsContainer::GetInstance().controls(this);
}

void Controls::Update(float) {
    for (auto &command : commands_) {
        if (command->IsConditionSatisfied())
            command->Execute();
    }
    controller_container_->Update();
}

void Controls::AddCommand(std::shared_ptr<Command> command) {
    commands_.push_back(command);
}

bool Controls::RemoveCommand(std::shared_ptr<Command> command) {
    for (unsigned int i = 0; i < commands_.size(); i++) {
        if (commands_[i] == command) {
            commands_.erase(commands_.begin() + i);
            return true;
        }
    }
    return false;
}

}