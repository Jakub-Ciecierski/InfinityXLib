#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include <memory>
#include <functional>

#include <controls/controller/controller_types.h>

namespace ifx {

class Controlable;
class Controller;

using CommandFunction = std::function<void(std::shared_ptr<Controller>,
                                           std::shared_ptr<Controlable>)>;

struct CommandExecutable {
    CommandFunction execute_fuction;
    const std::shared_ptr<Controller> controller;
    std::shared_ptr<Controlable> object;
};

class Command {
public:
    Command(const CommandExecutable&& executable);

    virtual ~Command();

    virtual bool IsConditionSatisfied() = 0;
    void Execute();

private:
    CommandExecutable executable_;

};

}


#endif //PROJECT_COMMAND_H
