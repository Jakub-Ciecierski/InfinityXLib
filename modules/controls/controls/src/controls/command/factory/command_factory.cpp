#include "controls/command/factory/command_factory.h"

#include <controls/controls.h>
#include <controls/command/commands/keyboard_command.h>
#include <controls/controller/controller_container.h>
#include <controls/controller/controllers/keyboard_controller.h>
#include <controls/controller/controllers/mouse_controller.h>
#include <controls/command/commands/mouse_command.h>

namespace ifx {

CommandFactory::CommandFactory(std::shared_ptr<Controls> controls) :
        controls_(controls){}

CommandFactory::~CommandFactory(){}

std::shared_ptr<MouseCommand> CommandFactory::CreateMouseCommand(
        std::shared_ptr<Controlable> object,
        CommandFunction function,
        const MouseControllerEventType&& event_type){
    auto mouse_controller
            = controls_->controller_container()->mouse_controller();
    auto event = mouse_controller->GetEvent(event_type.key);

    auto command = std::make_shared<MouseCommand>(
            CommandExecutable{function, mouse_controller, object},
            MouseCommandCondition{event, event_type.callback}
    );

    return command;
}

std::shared_ptr<KeyboardCommand> CommandFactory::CreateKeyboardCommand(
        std::shared_ptr<Controlable> object,
        CommandFunction function,
        const KeyboardControllerEventType&& event_type){
    auto keyboard_controller
            = controls_->controller_container()->keyboard_controller();
    auto event = keyboard_controller->GetEvent(event_type.key);

    auto command = std::make_shared<KeyboardCommand>(
            CommandExecutable{function, keyboard_controller, object},
            KeyboardCommandCondition{event, event_type.callback}
    );

    return command;
}

std::shared_ptr<MouseScrollCommand> CommandFactory::CreateMouseScrollCommand(){
    return nullptr;
}

}