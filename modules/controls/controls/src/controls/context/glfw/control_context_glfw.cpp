#include "controls/context/glfw/control_context_glfw.h"

#include <controls/context/glfw/controls_callbacks_glfw.h>

#include <GLFW/glfw3.h>

namespace ifx {

ControlContextGLFW::ControlContextGLFW(){}

ControlContextGLFW::~ControlContextGLFW(){}

bool ControlContextGLFW::InitAndSetupNativeCallbacks(void *native_window){
    if(glfwInit() != GL_TRUE)
        return false;

    auto glfw_window = (GLFWwindow*)native_window;

    glfwSetKeyCallback(glfw_window,
                       glfw_callbacks::key_callback);

    glfwSetCursorPosCallback(glfw_window,
                             glfw_callbacks::mouse_callback);
    glfwSetMouseButtonCallback(glfw_window,
                               glfw_callbacks::mouse_button_callback);
    glfwSetScrollCallback(glfw_window,
                          glfw_callbacks::mousescroll_callback);
    glfwSetCharCallback(glfw_window,
                        glfw_callbacks::char_callback);

    return true;
}

bool ControlContextGLFW::Terminate(){
    glfwTerminate();
    return true;
}

}