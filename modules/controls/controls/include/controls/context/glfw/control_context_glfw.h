#ifndef PROJECT_CONTROL_CONTEXT_GLFW_H
#define PROJECT_CONTROL_CONTEXT_GLFW_H

#include <controls/context/control_context.h>

namespace ifx {

namespace glfw_callbacks {
struct ExternalCallbacks;
}

class ControlContextGLFW : public ControlContext {
public:

    ControlContextGLFW();

    ~ControlContextGLFW();

    virtual bool InitAndSetupNativeCallbacks(void *) override;
    virtual bool Terminate() override;

    void SetExternalCallbacks(const glfw_callbacks::ExternalCallbacks &external_callbacks);

private:
};
}

#endif //PROJECT_CONTROL_CONTEXT_GLFW_H
