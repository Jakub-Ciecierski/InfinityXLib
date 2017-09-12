#ifndef PROJECT_MOUSE_COMMAND_H
#define PROJECT_MOUSE_COMMAND_H

#include <controls/command/command.h>

namespace ifx {

class MouseControllerEvent;

struct MouseCommandCondition {
    std::shared_ptr<MouseControllerEvent> event_;
    MouseControllerCallbackType type_;
};

class MouseCommand : public Command {
public:
    MouseCommand(const CommandExecutable &&executable,
                 const MouseCommandCondition &&mouse_condition);

    virtual ~MouseCommand();

    virtual bool IsConditionSatisfied() override;
private:
    MouseCommandCondition condition_;

};
}

#endif //PROJECT_MOUSE_COMMAND_H
