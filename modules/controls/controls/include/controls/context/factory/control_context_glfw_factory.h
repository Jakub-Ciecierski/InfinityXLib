#ifndef PROJECT_CONTROL_CONTEXT_GLFW_FACTORY_H
#define PROJECT_CONTROL_CONTEXT_GLFW_FACTORY_H

#include "controls/context/factory/control_context_factory.h"

namespace ifx {

class ControlContextGLFWFactory : public ControlContextFactory {
public:

    ControlContextGLFWFactory();

    ~ControlContextGLFWFactory();

    virtual std::shared_ptr<ControlContext> Create() override;
private:
};
}

#endif //PROJECT_CONTROL_CONTEXT_GLFW_FACTORY_H
