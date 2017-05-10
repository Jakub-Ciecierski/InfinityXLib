#include "graphics/rendering/window/window.h"

#include <controls/controls_events.h>
#include <controls/context/control_context.h>

#include <graphics/rendering/window/windows_container.h>
#include <graphics/rendering/context/rendering_context.h>

#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

namespace ifx {

Window::Window(int width, int height, std::string name) :
        width_(width), height_(height), name(name),
        rendering_context_(nullptr){
    WindowsContainer::GetInstance().AddWindow(this);
}

Window::~Window() {}

bool Window::Init(std::shared_ptr<RenderingContext> rendering_context,
                  std::shared_ptr<ControlContext> control_context){
    rendering_context_ = rendering_context;
    control_context_ = control_context;

    glfwWindow
            = (GLFWwindow*) rendering_context_->InitAndCreateNativeWindowHandle(
            name, &width_, &height_);

    control_context_->InitAndSetupNativeCallbacks(
            static_cast<void *>(glfwWindow));

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwSetFramebufferSizeCallback(glfwWindow, GLFWframebuffersizefun);

    return true;
}

void Window::Resize(int width, int height){
    width_ = width;
    height_ = height;
    setViewport();
}

void Window::HandleEvents() {
    ControlsEvents& controls = ControlsEvents::GetInstance();
    const Keys& keys = controls.keyboard_keys();

    if (keys[GLFW_KEY_ESCAPE]){
        glfwSetWindowShouldClose(glfwWindow, GL_TRUE);
    }
}

void Window::Update(float) {
    glfwSwapBuffers(getHandle());
    glfwPollEvents();

    HandleEvents();
}

void Window::setViewport() {
    glfwGetFramebufferSize(glfwWindow, &width_, &height_);

    glViewport(0, 0, width_, height_);
}

int Window::ShouldClose() {
    return glfwWindowShouldClose(glfwWindow);
}

GLFWwindow *Window::getHandle() {
    return glfwWindow;
}

void Window::ShowCursor(){
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::HideCursor(){
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void GLFWframebuffersizefun(GLFWwindow* glfw_window, int width, int height){
    Window* window = WindowsContainer::GetInstance().GetWindow(glfw_window);
    if(window){
        window->Resize(width, height);
    }else{
        std::cout << "No Window Found" << std::endl;
    }
}

}