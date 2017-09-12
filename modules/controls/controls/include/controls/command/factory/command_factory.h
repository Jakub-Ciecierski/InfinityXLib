#ifndef PROJECT_COMMAND_FACTORY_H
#define PROJECT_COMMAND_FACTORY_H

#include <memory>

#include <controls/controller/controller_types.h>

namespace ifx {

class MouseCommand;
class KeyboardCommand;
class MouseScrollCommand;
class Controls;
class Controlable;
class Controller;

using CommandFunction = std::function<void(std::shared_ptr<Controller>,
                                           std::shared_ptr<Controlable>)>;

class CommandFactory {
public:

    CommandFactory(std::shared_ptr<Controls> controls);

    ~CommandFactory();

    std::shared_ptr<MouseCommand> CreateMouseCommand(
        std::shared_ptr<Controlable> object,
        CommandFunction function,
        const MouseControllerEventType &&event_type);

    std::shared_ptr<KeyboardCommand> CreateKeyboardCommand(
        std::shared_ptr<Controlable> object,
        CommandFunction function,
        const KeyboardControllerEventType &&event_type);

    std::shared_ptr<MouseScrollCommand> CreateMouseScrollCommand();

private:
    std::shared_ptr<Controls> controls_;
};
}

#endif //PROJECT_COMMAND_FACTORY_H
