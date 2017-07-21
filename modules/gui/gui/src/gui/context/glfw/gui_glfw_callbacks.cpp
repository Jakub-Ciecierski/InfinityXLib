#include "gui/context/glfw/gui_glfw_callbacks.h"

#include <GLFW/glfw3.h>
#include <imgui/impl/imgui_impl_glfw_gl3.h>

namespace ifx {

namespace gui_glfw_callbacks{

bool key_callback(GLFWwindow *window, int key,
                  int scancode, int action, int mode){
    if(ImGui::GetIO().WantCaptureKeyboard){
        ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mode);
        return false;
    }
    ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mode);
    return true;
}

bool mouse_callback(GLFWwindow *window,
                    double xpos, double ypos){
    return true;
}

bool mouse_button_callback(GLFWwindow *window,
                           int button, int action, int mods){
    if(ImGui::GetIO().WantCaptureMouse){
        ImGui_ImplGlfwGL3_MouseButtonCallback(window, button, action, mods);
        return false;
    }
    ImGui_ImplGlfwGL3_MouseButtonCallback(window, button, action, mods);
    return true;
}

bool mousescroll_callback(GLFWwindow *window,
                          double xoffset, double yoffset){
    if(ImGui::GetIO().WantCaptureMouse){
        ImGui_ImplGlfwGL3_ScrollCallback(window, xoffset, yoffset);
        return false;
    }
    ImGui_ImplGlfwGL3_ScrollCallback(window, xoffset, yoffset);
    return true;
}

bool char_callback(GLFWwindow *window, unsigned int c){
    ImGui_ImplGlfwGL3_CharCallback(window, c);
    return true;
}

}
}

