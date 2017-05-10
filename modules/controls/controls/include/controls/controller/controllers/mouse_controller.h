#ifndef PROJECT_MOUSE_INPUT_H
#define PROJECT_MOUSE_INPUT_H

#include <memory>

#include <controls/controller/controller.h>
#include <controls/controller/controller_types.h>

namespace ifx {

class MouseControllerEvent;
class MouseScrollControllerEvent;

struct MousePosition {
    float x;
    float y;
};

struct MouseControllerEvents {
    std::shared_ptr<MouseControllerEvent> left_button;
    std::shared_ptr<MouseControllerEvent> right_button;
    std::shared_ptr<MouseControllerEvent> middle_button;
    std::shared_ptr<MouseScrollControllerEvent> scroll_input_event;
};

class MouseController : public Controller {
public:
    MouseController(const MouseControllerEvents&& mouse_input_events);

    ~MouseController();

    const MousePosition& GetCurrentPosition(){return current_position_;}
    const MousePosition& GetPreviousPosition(){return previous_position_;}
    const MousePosition& GetScrollOffset(){return scroll_offset_;}

    void SetCurrentPosition(const MousePosition&& pos);
    void SetScrollOffset(const MousePosition&& pos);

    std::shared_ptr<MouseControllerEvent> GetEvent(
            MouseControllerKeyType type);

    virtual void Update(float time_delta = 0) override;

private:
    MousePosition current_position_;
    MousePosition previous_position_;

    MousePosition scroll_offset_;
};
}


#endif //PROJECT_MOUSE_INPUT_H
