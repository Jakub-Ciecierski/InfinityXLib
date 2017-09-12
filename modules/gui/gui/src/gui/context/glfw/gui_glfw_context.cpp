#include "gui/context/glfw/gui_glfw_context.h"

#include <imgui/impl/imgui_impl_glfw_gl3.h>

#include <GLFW/glfw3.h>

#include <gui/context/glfw/gui_glfw_callbacks.h>

#include <controls/context/glfw/control_context_glfw.h>
#include <controls/context/glfw/controls_callbacks_glfw.h>
#include <iostream>

namespace ifx {

GUIGLFWContext::GUIGLFWContext() {}

GUIGLFWContext::~GUIGLFWContext() {}

bool GUIGLFWContext::Init(void *native_window,
                          std::shared_ptr<ControlContext> control_context) {
    if (!ImGui_ImplGlfwGL3_Init((GLFWwindow *) native_window, false))
        return false;

    auto glfw_control_context =
        std::static_pointer_cast<ControlContextGLFW>(control_context);
    if (!glfw_control_context)
        throw std::invalid_argument("ControlContextGLFW required");

    glfw_control_context
        ->SetExternalCallbacks(glfw_callbacks::ExternalCallbacks{
            &gui_glfw_callbacks::key_callback,
            &gui_glfw_callbacks::mouse_callback,
            &gui_glfw_callbacks::mouse_button_callback,
            &gui_glfw_callbacks::mousescroll_callback,
            &gui_glfw_callbacks::char_callback
        });

    return true;
}

bool GUIGLFWContext::Terminate() {
    ImGui_ImplGlfwGL3_Shutdown();

    return true;
}

void GUIGLFWContext::NewFrame() {
    // TODO is glPolygonMode really needed ?
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    ImGui_ImplGlfwGL3_NewFrame();
}

void GUIGLFWContext::Render() {
    ImGui::Render();
}

}