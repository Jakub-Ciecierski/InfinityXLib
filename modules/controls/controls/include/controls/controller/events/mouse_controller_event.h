#ifndef PROJECT_MOUSE_INPUT_EVENT_H
#define PROJECT_MOUSE_INPUT_EVENT_H

#include <controls/controller/controller_event.h>

#include <controls/controller/controller_types.h>

namespace ifx {

class MouseControllerEvent : public ControllerEvent {
public:

    MouseControllerEvent(const MouseControllerKeyType&& type);

    virtual ~MouseControllerEvent();

    const MouseControllerKeyType& type(){return type_;}

private:
    MouseControllerKeyType type_;
};
}


#endif //PROJECT_MOUSE_INPUT_EVENT_H
