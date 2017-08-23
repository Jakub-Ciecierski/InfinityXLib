#ifndef PROJECT_GUI_CONTEXT_H
#define PROJECT_GUI_CONTEXT_H

#include <memory>

namespace ifx {

class ControlContext;

class GUIContext {
public:

    GUIContext() = default;
    virtual ~GUIContext() = default;

    virtual bool Init(void* native_window,
                      std::shared_ptr<ControlContext> control_context) = 0;
    virtual bool Terminate() = 0;

    virtual void NewFrame() = 0;
    virtual void Render() = 0;

private:
};
}


#endif //PROJECT_GUI_CONTEXT_H
