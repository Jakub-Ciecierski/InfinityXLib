#ifndef PROJECT_KEY_MAPPING_GLFW_H
#define PROJECT_KEY_MAPPING_GLFW_H

#include <controls/controller/controller_types.h>

namespace ifx {

int KeyIFX2GLFW(KeyboardControllerKeyType ifx_key);
KeyboardControllerKeyType KeyGLFW2IFX(int glfw_key);

int KeyboardCallbackIFX2GLFW(KeyboardControllerCallbackType ifx_key);
KeyboardControllerCallbackType KeyboardCallbackGLFW2IFX(int glfw_key);

}

#endif //PROJECT_KEY_MAPPING_GLFW_H
