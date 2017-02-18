#include "graphics/rendering/window/window.h"

#include <controls/controls_events.h>
#include <graphics/rendering/window/windows_container.h>

#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

namespace ifx {

Window::Window(int width, int height, std::string name) :
        width_(width), height_(height), name(name) {
    init();
    setViewport();

    WindowsContainer::GetInstance().AdddWindow(this);
}

Window::~Window() {
    Terminate();
}

void Window::Resize(int width, int height){
    width_ = width;
    height_ = height;
    setViewport();
}

void Window::Terminate(){
    glfwTerminate();
}

void Window::HandleEvents() {
    ControlsEvents& controls = ControlsEvents::GetInstance();
    const Keys& keys = controls.keyboard_keys();

    if (keys[GLFW_KEY_ESCAPE]){
        glfwSetWindowShouldClose(glfwWindow, GL_TRUE);
    }
}

void Window::init() {
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindow = glfwCreateWindow(width_, height_,
                                  name.c_str(), nullptr, nullptr);
    glfwSetFramebufferSizeCallback(glfwWindow, GLFWframebuffersizefun);

    if (glfwWindow == nullptr) {
        throw new std::invalid_argument("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(glfwWindow);
}

void Window::setViewport() {
    glfwGetFramebufferSize(glfwWindow, &width_, &height_);

    glViewport(0, 0, width_, height_);
}

int Window::shouldClose() {
    return glfwWindowShouldClose(glfwWindow);
}

void Window::update() {
    HandleEvents();
    glfwPollEvents();
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