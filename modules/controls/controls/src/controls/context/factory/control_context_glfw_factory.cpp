#include "controls/context/factory/control_context_glfw_factory.h"

#include <controls/context/glfw/control_context_glfw.h>

namespace ifx {

ControlContextGLFWFactory::ControlContextGLFWFactory() {}

ControlContextGLFWFactory::~ControlContextGLFWFactory() {}

std::shared_ptr<ControlContext> ControlContextGLFWFactory::Create() {
    return std::make_shared<ControlContextGLFW>();
}

}