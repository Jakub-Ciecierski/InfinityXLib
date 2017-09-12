#ifndef PROJECT_CONTROL_CONTEXT_FACTORY_H
#define PROJECT_CONTROL_CONTEXT_FACTORY_H

#include <memory>

namespace ifx {

class ControlContext;

class ControlContextFactory {
public:

    ControlContextFactory();

    virtual ~ControlContextFactory();

    virtual std::shared_ptr<ControlContext> Create() = 0;

private:
};
}

#endif //PROJECT_CONTROL_CONTEXT_FACTORY_H
