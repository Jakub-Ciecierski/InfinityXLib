#ifndef PROJECT_SCROLL_INPUT_EVENT_H
#define PROJECT_SCROLL_INPUT_EVENT_H

#include <controls/controller/events/mouse_controller_event.h>

namespace ifx {

class MouseScrollControllerEvent : public MouseControllerEvent {
public:
    MouseScrollControllerEvent();

    ~MouseScrollControllerEvent();

    virtual bool IsPressed() override;
    virtual bool IsReleased() override;

    bool IsActivated();
    void SetActivated(bool value);

    virtual void Reset() override;

private:
    bool is_activated_;
};
}


#endif //PROJECT_SCROLL_INPUT_EVENT_H
