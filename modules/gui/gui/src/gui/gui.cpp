#include "gui/gui.h"

#include <gui/imgui/impl/imgui_impl_glfw_gl3.h>

#include <GLFW/glfw3.h>

namespace ifx {

GUI::GUI(GLFWwindow* window){
    ImGui_ImplGlfwGL3_Init(window, false);
}

GUI::~GUI(){
    ImGui_ImplGlfwGL3_Shutdown();
}

void GUI::NewFrame(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    ImGui_ImplGlfwGL3_NewFrame();
}

}