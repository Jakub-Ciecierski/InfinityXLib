#include "controls/glfw_callbacks.h"

#include <controls/controls_events.h>
#include "gui/imgui/impl/imgui_impl_glfw_gl3.h"

namespace ifx {

void key_callback(GLFWwindow *window, int key,
                  int scancode, int action, int mode) {
    if(ImGui::GetIO().WantCaptureKeyboard){
        ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mode);
        return;
    }
    // Duplication on purpose.
    ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mode);
    ControlsEvents::GetInstance().OnKeyboardEvent(action, key);
}

void mouse_callback(GLFWwindow *window,
                    double x, double y) {
    ControlsEvents::GetInstance().OnMouseEvent(x, y);
}

void mouse_button_callback(GLFWwindow *window,
                           int button, int action, int mods) {
    ControlsEvents& controls = ControlsEvents::GetInstance();

    if(ImGui::GetIO().WantCaptureMouse){
        ImGui_ImplGlfwGL3_MouseButtonCallback(window, button, action, mods);
        return;
    }

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    controls.OnMouseEvent(xpos, ypos);

    int state_left = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int state_right = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    int state_middle = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);

    bool left_pressed = state_left == GLFW_PRESS;
    bool right_pressed = state_right == GLFW_PRESS;
    bool middle_pressed = state_middle == GLFW_PRESS;

    controls.OnMouseButtonEvent(MouseButtonType::BUTTON_LEFT, left_pressed,
                                xpos, ypos);
    controls.OnMouseButtonEvent(MouseButtonType::BUTTON_RIGHT, right_pressed,
                                xpos, ypos);
    controls.OnMouseButtonEvent(MouseButtonType::BUTTON_MIDDLE,
                                middle_pressed,
                                xpos, ypos);
}

void mousescroll_callback(GLFWwindow *window,
                          double xoffset, double yoffset) {
    if(ImGui::GetIO().WantCaptureMouse){
        ImGui_ImplGlfwGL3_ScrollCallback(window, xoffset, yoffset);
        return;
    }
    ControlsEvents::GetInstance().OnMouseScrollEvent(xoffset, yoffset);
}

void char_callback(GLFWwindow* window, unsigned int c){
    ImGui_ImplGlfwGL3_CharCallback(window, c);
}

}