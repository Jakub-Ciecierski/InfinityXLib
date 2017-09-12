#ifndef PROJECT_CONTROLLABLE_OBJECT_H
#define PROJECT_CONTROLLABLE_OBJECT_H

#include <controls/controlable.h>

namespace ifx {

class ControlableObject : public Controlable {
public:

    ControlableObject();

    ~ControlableObject();

    bool value() { return value_; }
    void value(bool v) { value_ = v; }

private:
    bool value_;
};
}

#endif //PROJECT_CONTROLLABLE_OBJECT_H
