#ifndef PROJECT_CONTROLS_UPDATE_H
#define PROJECT_CONTROLS_UPDATE_H

#include <common/updatable.h>

#include <memory>
#include <vector>

namespace ifx {

class Command;
class ControlContext;
class ControllerContainer;

/**
 * Contains all commands set up by the user.
 * Used to update each frame (or variable frames).
 * For each update, all commands are checked against input conditions and
 * are executed if the condition is satisfied.
 */
class Controls : public Updatable {
public:
    Controls(std::shared_ptr<ControlContext>,
             std::shared_ptr<ControllerContainer>);
    ~Controls() = default;

    std::shared_ptr<ControllerContainer> controller_container() {
        return controller_container_;
    }

    virtual void Update(float = 0) override;

    void AddCommand(std::shared_ptr<Command> command);
    bool RemoveCommand(std::shared_ptr<Command> command);

private:
    std::vector<std::shared_ptr<Command>> commands_;

    std::shared_ptr<ControlContext> control_context_;

    std::shared_ptr<ControllerContainer> controller_container_;
};
}

#endif //PROJECT_CONTROLS_UPDATE_H
