#ifndef PROJECT_RENDERING_CONTEXT_OPENGL_FACTORY_H
#define PROJECT_RENDERING_CONTEXT_OPENGL_FACTORY_H

#include <memory>

#include "graphics/rendering/context/factory/rendering_context_factory.h"

namespace ifx {

class RenderingContext;

class RenderingContextOpenglFactory : public RenderingContextFactory {
public:

    RenderingContextOpenglFactory();

    ~RenderingContextOpenglFactory();

    virtual std::shared_ptr<RenderingContext> Create() override;

private:
};
}

#endif //PROJECT_RENDERING_CONTEXT_OPENGL_FACTORY_H
