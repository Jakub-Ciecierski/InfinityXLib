#include "gui_glfw_context.h"

#include <imgui/impl/imgui_impl_glfw_gl3.h>

#include <GLFW/glfw3.h>

namespace ifx {

GUIGLFWContext::GUIGLFWContext() {}

GUIGLFWContext::~GUIGLFWContext() {}

bool GUIGLFWContext::Init(void *native_window) {
    if(!ImGui_ImplGlfwGL3_Init((GLFWwindow*)native_window, false))
        return false;

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