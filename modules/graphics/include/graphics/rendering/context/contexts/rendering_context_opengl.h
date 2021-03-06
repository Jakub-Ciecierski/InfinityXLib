#ifndef PROJECT_RENDERING_CONTEXT_OPENGL_H
#define PROJECT_RENDERING_CONTEXT_OPENGL_H

#include "graphics/rendering/context/rendering_context.h"

namespace ifx {

class RenderingContextOpengl : public RenderingContext{
public:

    RenderingContextOpengl() = default;
    ~RenderingContextOpengl() = default;

    virtual bool Terminate() override;

    virtual void*InitAndCreateNativeWindowHandle(std::string name,
                                                 int *width, int *height) override;
private:
    bool InitGLFW();
    bool InitGLEW();

    bool TerminateGLFW();
    bool TerminateGLEW();
};
}


#endif //PROJECT_RENDERING_CONTEXT_OPENGL_H
