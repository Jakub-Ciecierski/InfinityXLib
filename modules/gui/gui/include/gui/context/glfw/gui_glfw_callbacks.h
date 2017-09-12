#ifndef PROJECT_GUI_GLFW_CALLBACKS_H
#define PROJECT_GUI_GLFW_CALLBACKS_H

struct GLFWwindow;

namespace ifx {

namespace gui_glfw_callbacks {

bool key_callback(GLFWwindow *window, int key,
                  int scancode, int action, int mode);

bool mouse_callback(GLFWwindow *window,
                    double xpos, double ypos);

bool mouse_button_callback(GLFWwindow *window,
                           int button, int action, int mods);

bool mousescroll_callback(GLFWwindow *window,
                          double xoffset, double yoffset);

bool char_callback(GLFWwindow *window, unsigned int c);

}
}

#endif //PROJECT_GUI_GLFW_CALLBACKS_H
