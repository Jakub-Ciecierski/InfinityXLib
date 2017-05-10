#ifndef PROJECT_INPUT_EVENTS_CONTAINER_H
#define PROJECT_INPUT_EVENTS_CONTAINER_H

#include <memory>

#include <common/updatable.h>

namespace ifx {

class MouseController;
class KeyboardController;

/**
 * Contains all Input controllers available in the system.
 * New input controlers should be added here.
 */
class ControllerContainer : public Updatable{
public:

    ControllerContainer(std::shared_ptr<MouseController> mouse_input,
                        std::shared_ptr<KeyboardController> keyboard_input);
    ~ControllerContainer();

    std::shared_ptr<MouseController> mouse_controller(){return mouse_controller_;}
    std::shared_ptr<KeyboardController> keyboard_controller(){return
                keyboard_controller_;}

    virtual void Update(float = 0) override;

private:
    std::shared_ptr<MouseController> mouse_controller_;
    std::shared_ptr<KeyboardController> keyboard_controller_;

};
}


#endif //PROJECT_INPUT_EVENTS_CONTAINER_H
