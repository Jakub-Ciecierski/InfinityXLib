#include "graphics/rendering/context/contexts/rendering_context_opengl.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

namespace ifx {

bool RenderingContextOpengl::Terminate() {
    if (!IsInit())
        return true;

    if (!TerminateGLFW())
        return false;
    if (!TerminateGLEW())
        return false;
    return true;
}

bool RenderingContextOpengl::InitGLFW() {
    if (glfwInit() != GL_TRUE)
        return false;

    // OpenGL version required
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    // No legacy functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}

bool RenderingContextOpengl::InitGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        return false;
    return true;
}

void *RenderingContextOpengl::InitAndCreateNativeWindowHandle(std::string name,
                                                              int *width,
                                                              int *height) {
    if (!InitGLFW())
        throw new std::invalid_argument("Failed to initialize GLFW");

    auto glfwWindow = glfwCreateWindow(*width, *height,
                                       name.c_str(), nullptr, nullptr);
    if(!glfwWindow){
        throw new std::invalid_argument("Failed to create glfw window");
    }

    glfwMakeContextCurrent(glfwWindow);
    glfwGetFramebufferSize(glfwWindow, width, height);
    glViewport(0, 0, *width, *height);

    if (!InitGLEW())
        throw new std::invalid_argument("Failed to initialize GLEW");

    // VSync
    glfwSwapInterval(1);

    is_init_ = true;

    return (void *) glfwWindow;
}

bool RenderingContextOpengl::TerminateGLFW() {
    glfwTerminate();
    return true;
}

bool RenderingContextOpengl::TerminateGLEW() {
    return true;
}

}