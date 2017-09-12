#ifndef PROJECT_CONTEXT_FACTORY_H
#define PROJECT_CONTEXT_FACTORY_H

#include <memory>

namespace ifx {

class GUIContext;

class GUIContextFactory {
public:

    GUIContextFactory();

    virtual ~GUIContextFactory();

    virtual std::shared_ptr<GUIContext> Create() = 0;

private:
};
}

#endif //PROJECT_CONTEXT_FACTORY_H
