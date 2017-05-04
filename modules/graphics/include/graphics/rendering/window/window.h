#ifndef DUCK_WINDOW_H
#define DUCK_WINDOW_H

#include <string>
#include <memory>

#include <controls/event_handler.h>
#include <common/updatable.h>

struct GLFWwindow;

namespace ifx {

class RenderingContext;

/*
 * Windows Context, encapsulating the GLFW handle
 */
class Window : public EventHandler, public Updatable {

public:
    Window(int width, int height, std::string name);
    ~Window();

    int* width() {return &width_;}
    int* height() {return &height_;}

    bool Init(std::shared_ptr<RenderingContext> rendering_context);

    void Resize(int width, int height);

    // Overridden from EvenHandler
    void HandleEvents() override;

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
};

void GLFWframebuffersizefun(GLFWwindow *, int, int);

}

#endif //DUCK_WINDOW_H
