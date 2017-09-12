#ifndef PROJECT_CONTROL_CONTEXT_H
#define PROJECT_CONTROL_CONTEXT_H

namespace ifx {

class ControlContext {
public:

    ControlContext();

    virtual ~ControlContext();

    virtual bool InitAndSetupNativeCallbacks(void *) = 0;
    virtual bool Terminate() = 0;
private:
};
}

#endif //PROJECT_CONTROL_CONTEXT_H
