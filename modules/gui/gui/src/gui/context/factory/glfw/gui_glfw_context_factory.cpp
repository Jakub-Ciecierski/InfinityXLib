#include "gui/context/factory/glfw/gui_glfw_context_factory.h"

#include <gui/context/glfw/gui_glfw_context.h>

namespace ifx {

GUIGLFWContextFactory::GUIGLFWContextFactory() {}

GUIGLFWContextFactory::~GUIGLFWContextFactory() {}

std::shared_ptr<GUIContext> GUIGLFWContextFactory::Create() {
    return std::make_shared<GUIGLFWContext>();
}
}