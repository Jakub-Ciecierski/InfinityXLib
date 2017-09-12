#ifndef PROJECT_RENDERING_CONTEXT_FACTORY_H
#define PROJECT_RENDERING_CONTEXT_FACTORY_H

#include <memory>

namespace ifx {

class RenderingContext;

class RenderingContextFactory {
public:

    RenderingContextFactory();
    virtual ~RenderingContextFactory();

    virtual std::shared_ptr<RenderingContext> Create() = 0;

private:
};
}

#endif //PROJECT_RENDERING_CONTEXT_FACTORY_H
