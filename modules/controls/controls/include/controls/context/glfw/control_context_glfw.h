#ifndef PROJECT_CONTROL_CONTEXT_GLFW_H
#define PROJECT_CONTROL_CONTEXT_GLFW_H

#include <controls/context/control_context.h>

namespace ifx {

class ControlContextGLFW : public ControlContext {
public:

    ControlContextGLFW();

    ~ControlContextGLFW();

    virtual bool InitAndSetupNativeCallbacks(void *) override;
    virtual bool Terminate() override;

private:
};
}


#endif //PROJECT_CONTROL_CONTEXT_GLFW_H
