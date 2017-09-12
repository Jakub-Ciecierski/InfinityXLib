#ifndef PROJECT_CONTROL_CONTEXT_IMPL_H
#define PROJECT_CONTROL_CONTEXT_IMPL_H

#include <controls/context/control_context.h>

namespace ifx {

class ControlContextImpl : public ControlContext {
public:

    ControlContextImpl();

    ~ControlContextImpl();

    virtual bool InitAndSetupNativeCallbacks(void *) override;
    virtual bool Terminate() override;

private:
};
}

#endif //PROJECT_CONTROL_CONTEXT_IMPL_H
