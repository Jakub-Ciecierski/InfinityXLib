#ifndef DUCK_WINDOW_H
#define DUCK_WINDOW_H

#include <string>
#include <memory>

#include <common/updatable.h>
#include "graphics/rendering/window/window_subject.h"

struct GLFWwindow;

namespace ifx {

class RenderingContext;
class ControlContext;
class WindowObserver;

/*
 * Windows Context, encapsulating the GLFW handle
 */
class Window : public Updatable, public WindowSubject {

public:
    Window(int width, int height, std::string name);
    ~Window() = default;

    int* width() {return &width_;}
    int* height() {return &height_;}

    bool Init(std::shared_ptr<RenderingContext> rendering_context,
              std::shared_ptr<ControlContext> control_context);

    void Resize(int width, int height);

    // Overridden from Updatable
    virtual void Update(float time_delta = 0) override;

    int ShouldClose();

    GLFWwindow* getHandle();

    void ShowCursor();
    void HideCursor();

private:
    GLFWwindow* glfwWindow;

    int width_;
    int height_;
    std::string name;

    void setViewport();

    std::shared_ptr<RenderingContext> rendering_context_;
    std::shared_ptr<ControlContext> control_context_;
};

void GLFWframebuffersizefun(GLFWwindow *, int, int);

}

#endif //DUCK_WINDOW_H
