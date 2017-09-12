#ifndef PROJECT_RENDERING_CONTEXT_H
#define PROJECT_RENDERING_CONTEXT_H

#include <string>

namespace ifx {

class RenderingContext {
public:

    RenderingContext();
    virtual ~RenderingContext();

    bool IsInit() { return is_init_; }

    virtual bool Terminate() = 0;

    virtual void *InitAndCreateNativeWindowHandle(std::string name,
                                                  int *width, int *height) = 0;
protected:
    bool is_init_;
};
}

#endif //PROJECT_RENDERING_CONTEXT_H
