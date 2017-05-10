#ifndef PROJECT_KEYBOARD_COMMAND_H
#define PROJECT_KEYBOARD_COMMAND_H

#include <controls/command/command.h>

#include <controls/controller/controller_types.h>

namespace ifx {

class KeyboardControllerEvent;

struct KeyboardCommandCondition {
    std::shared_ptr<KeyboardControllerEvent> event_;
    KeyboardControllerCallbackType type_;
};

class KeyboardCommand : public Command {
public:

    KeyboardCommand(const CommandExecutable&& executable,
                    const KeyboardCommandCondition&& condition);

    ~KeyboardCommand();

    virtual bool IsConditionSatisfied() override;
private:

    KeyboardCommandCondition condition_;
};
}


#endif //PROJECT_KEYBOARD_COMMAND_H
