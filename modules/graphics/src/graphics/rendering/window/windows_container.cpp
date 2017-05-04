#include "graphics/rendering/window/windows_container.h"

#include <graphics/rendering/window/window.h>
#include <GLFW/glfw3.h>

namespace ifx {

WindowsContainer::WindowsContainer(){}
WindowsContainer::~WindowsContainer(){}

// static
WindowsContainer& WindowsContainer::GetInstance(){
    static WindowsContainer container;
    return container;
}

void WindowsContainer::AddWindow(Window* window){
    windows_.push_back(window);
}

Window* WindowsContainer::GetWindow(GLFWwindow* glfw_window){
    for(auto window : windows_)
        if(window->getHandle() == glfw_window)
            return window;
    return nullptr;
}



}