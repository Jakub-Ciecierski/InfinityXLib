#ifndef PROJECT_GUI_GLFW_CONTEXT_H
#define PROJECT_GUI_GLFW_CONTEXT_H

#include <gui/context/gui_context.h>

namespace ifx {

class GUIGLFWContext : public GUIContext {
public:

    GUIGLFWContext();

    virtual ~GUIGLFWContext();

    bool Init(void *native_window, std::shared_ptr<ControlContext> control_context) override;
    bool Terminate() override;

    void NewFrame() override;
    void Render() override;

private:
};
}


#endif //PROJECT_GUI_GLFW_CONTEXT_H
