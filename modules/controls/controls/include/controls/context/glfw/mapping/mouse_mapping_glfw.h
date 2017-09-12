#ifndef PROJECT_MOUSE_MAPPING_GLFW_H
#define PROJECT_MOUSE_MAPPING_GLFW_H

#include <controls/controller/controller_types.h>

namespace ifx {

int MouseKeyIFX2GLFW(MouseControllerKeyType ifx_key);
MouseControllerKeyType MouseGLFW2IFX(int glfw_key);

int MouseCallbackIFX2GLFW(MouseControllerCallbackType ifx_key);
MouseControllerCallbackType MouseCallbackGLFW2IFX(int glfw_key);

}

#endif //PROJECT_MOUSE_MAPPING_GLFW_H
