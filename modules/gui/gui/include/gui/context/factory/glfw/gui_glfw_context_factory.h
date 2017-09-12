#ifndef PROJECT_GUI_GLFW_CONTEXT_FACTORY_H
#define PROJECT_GUI_GLFW_CONTEXT_FACTORY_H

#include <gui/context/factory/gui_context_factory.h>

namespace ifx {

class GUIGLFWContextFactory : public GUIContextFactory {
public:

    GUIGLFWContextFactory();

    ~GUIGLFWContextFactory();

    std::shared_ptr<GUIContext> Create() override;

private:
};
}

#endif //PROJECT_GUI_GLFW_CONTEXT_FACTORY_H
