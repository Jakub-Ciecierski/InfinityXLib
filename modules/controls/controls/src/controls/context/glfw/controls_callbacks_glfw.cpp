#include "controls/context/glfw/controls_callbacks_glfw.h"

#include <controls/context/glfw/mapping/mouse_mapping_glfw.h>
#include <controls/context/glfw/mapping/key_mapping_glfw.h>
#include <controls/controls_container.h>
#include <controls/controls.h>
#include <controls/controller/controller_container.h>
#include <controls/controller/controllers/keyboard_controller.h>
#include <controls/controller/controllers/mouse_controller.h>
#include "controls/controller/events/keyboard_controller_event.h"
#include "controls/controller/events/mouse_controller_event.h"
#include "controls/controller/events/mouse_scroll_controller_event.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace ifx {

namespace glfw_callbacks {

ExternalCallbacks external_callbacks_{nullptr, nullptr,
                                      nullptr, nullptr,
                                      nullptr};

void key_callback(GLFWwindow *window, int key,
                  int scancode, int action, int mode) {
    if(external_callbacks_.key_callback)
        if(!external_callbacks_.key_callback(window, key, scancode, action, mode))
            return;

    // Map
    auto ifx_key = ifx::KeyGLFW2IFX(key);
    auto ifx_callback = ifx::KeyboardCallbackGLFW2IFX(action);

    // Error
    if(ifx_key == KeyboardControllerKeyType::UNKNOWN)
        return;

    // Set status
    auto controls = ControlsContainer::GetInstance().controls();
    auto event = controls->controller_container()->keyboard_controller()->
            GetEvent(ifx_key);
    if(!event)
        return;

    switch (ifx_callback) {
        case KeyboardControllerCallbackType::PRESSED:
            event->OnPressed();
            break;
        case KeyboardControllerCallbackType::RELEASED:
            event->OnReleased();
            break;
        case KeyboardControllerCallbackType::UNKNOWN:
            break;
    }
}

void mouse_callback(GLFWwindow *window,
                    double xpos, double ypos) {
    if(external_callbacks_.mouse_callback)
        if(!external_callbacks_.mouse_callback(window, xpos, ypos))
            return;

    auto controls = ControlsContainer::GetInstance().controls();
    auto mouse_controller = controls->controller_container()
            ->mouse_controller();
    mouse_controller->SetCurrentPosition(MousePosition{(float)xpos,
                                                       (float)ypos});
}

void mouse_button_callback(GLFWwindow *window,
                           int button, int action, int mods) {
    if(external_callbacks_.mouse_button_callback)
        if(!external_callbacks_.mouse_button_callback(window, button, action, mods))
            return;

    auto ifx_key = MouseGLFW2IFX(button);
    auto ifx_callback = MouseCallbackGLFW2IFX(action);

    if(ifx_key == MouseControllerKeyType::UNKNOWN)
        return;

    auto controls = ControlsContainer::GetInstance().controls();
    auto event = controls->controller_container()->mouse_controller()->
            GetEvent(ifx_key);
    if(!event)
        return;

    switch (ifx_callback) {
        case MouseControllerCallbackType::PRESSED:
            event->OnPressed();
            break;
        case MouseControllerCallbackType::RELEASED:
            event->OnReleased();
            break;
        case MouseControllerCallbackType::SCROLL_ACTIVE:
            // handled by different callback
            break;
        case MouseControllerCallbackType::UNKNOWN:
            break;
    }
}

void mousescroll_callback(GLFWwindow *window,
                          double xoffset, double yoffset) {
    if(external_callbacks_.mousescroll_callback)
        if(!external_callbacks_.mousescroll_callback(window, xoffset, yoffset))
            return;

    auto controls = ControlsContainer::GetInstance().controls();
    auto mouse_controller = controls->controller_container()->
            mouse_controller();
    auto scroll_event = mouse_controller->
            GetEvent(ifx::MouseControllerKeyType::MOUSE_SCROLL);
    if(!scroll_event)
        return;

    std::static_pointer_cast<MouseScrollControllerEvent>(scroll_event)->
            SetActivated(true);

    mouse_controller->SetScrollOffset(MousePosition{(float)xoffset,
                                                    (float)yoffset});
}

void char_callback(GLFWwindow *window, unsigned int c) {
    if(external_callbacks_.char_callback)
        if(!external_callbacks_.char_callback(window, c))
            return;
}

};
};