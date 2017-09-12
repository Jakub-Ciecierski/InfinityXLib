#ifndef PROJECT_INPUT_EVENT_H
#define PROJECT_INPUT_EVENT_H

namespace ifx {

class ControllerEvent {
public:

    virtual ~ControllerEvent();

    virtual bool IsPressed();
    virtual bool IsReleased();

    virtual void Reset();

    virtual void OnPressed();
    virtual void OnReleased();

protected:
    ControllerEvent();

    bool is_pressed_;
    bool is_released_;
};
}

#endif //PROJECT_INPUT_EVENT_H
