#include <controls/context/glfw/mapping/mouse_mapping_glfw.h>

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace ifx {

int MouseKeyIFX2GLFW(MouseControllerKeyType ifx_key){
    switch(ifx_key){
        case MouseControllerKeyType::MOUSE_LEFT:
            return GLFW_MOUSE_BUTTON_LEFT;
        case MouseControllerKeyType::MOUSE_RIGHT:
            return GLFW_MOUSE_BUTTON_RIGHT;
        case MouseControllerKeyType::MOUSE_MIDDLE:
            return GLFW_MOUSE_BUTTON_MIDDLE;
        case MouseControllerKeyType::MOUSE_SCROLL:
            throw std::invalid_argument("MouseControllerKeyType::MOUSE_SCROLL");
        case MouseControllerKeyType::UNKNOWN:
            throw std::invalid_argument("MouseControllerKeyType::UNKNOWN");
    }
    return -1;
}

MouseControllerKeyType MouseGLFW2IFX(int glfw_key){
    switch(glfw_key){
        case GLFW_MOUSE_BUTTON_LEFT:
            return MouseControllerKeyType::MOUSE_LEFT;
        case GLFW_MOUSE_BUTTON_RIGHT:
            return MouseControllerKeyType::MOUSE_RIGHT;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            return MouseControllerKeyType::MOUSE_MIDDLE;
        default:
            return MouseControllerKeyType::UNKNOWN;
    }
}

int MouseCallbackIFX2GLFW(MouseControllerCallbackType ifx_key){
    switch(ifx_key){
        case MouseControllerCallbackType::PRESSED:
            return GLFW_PRESS;
        case MouseControllerCallbackType::RELEASED:
            return GLFW_RELEASE;
        case MouseControllerCallbackType::UNKNOWN:
            throw std::invalid_argument("MouseControllerCallbackType::UNKNOWN");
        case MouseControllerCallbackType::SCROLL_ACTIVE:
            throw std::invalid_argument(
                    "MouseControllerCallbackType::SCROLL_ACTIVE");
    }
    return -1;
}

MouseControllerCallbackType MouseCallbackGLFW2IFX(int glfw_key){
    switch(glfw_key){
        case GLFW_PRESS:
            return MouseControllerCallbackType::PRESSED;
        case GLFW_RELEASE:
            return MouseControllerCallbackType::RELEASED;
        default:
            return MouseControllerCallbackType::UNKNOWN;
    }
}

}