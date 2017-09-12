#ifndef PROJECT_CONTROLS_CALLBACKS_GLFW_H
#define PROJECT_CONTROLS_CALLBACKS_GLFW_H

#include <functional>

struct GLFWwindow;

namespace ifx {

namespace glfw_callbacks {

void key_callback(GLFWwindow *window, int key,
                  int scancode, int action, int mode);

void mouse_callback(GLFWwindow *window,
                    double xpos, double ypos);

void mouse_button_callback(GLFWwindow *window,
                           int button, int action, int mods);

void mousescroll_callback(GLFWwindow *window,
                          double xoffset, double yoffset);

void char_callback(GLFWwindow *window, unsigned int c);

struct ExternalCallbacks {
    std::function<bool(GLFWwindow *window, int key,
                       int scancode, int action, int mode)> key_callback;
    std::function<bool(GLFWwindow *window,
                       double xpos, double ypos)> mouse_callback;
    std::function<bool(GLFWwindow *window,
                       int button, int action, int mods)> mouse_button_callback;
    std::function<bool(GLFWwindow *window,
                       double xoffset, double yoffset)> mousescroll_callback;
    std::function<bool(GLFWwindow *window, unsigned int c)> char_callback;
};

extern ExternalCallbacks external_callbacks_;

};
};

#endif //PROJECT_CONTROLS_CALLBACKS_GLFW_H
