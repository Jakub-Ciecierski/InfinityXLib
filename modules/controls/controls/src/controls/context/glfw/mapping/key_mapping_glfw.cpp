#include <controls/context/glfw/mapping/key_mapping_glfw.h>

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace ifx {

int KeyIFX2GLFW(KeyboardControllerKeyType ifx_key) {
    switch (ifx_key) {
        case KeyboardControllerKeyType::Q:return GLFW_KEY_Q;
        case KeyboardControllerKeyType::W:return GLFW_KEY_W;
        case KeyboardControllerKeyType::E:return GLFW_KEY_E;
        case KeyboardControllerKeyType::R:return GLFW_KEY_R;
        case KeyboardControllerKeyType::T:return GLFW_KEY_T;
        case KeyboardControllerKeyType::Y:return GLFW_KEY_Y;
        case KeyboardControllerKeyType::U:return GLFW_KEY_U;
        case KeyboardControllerKeyType::I:return GLFW_KEY_I;
        case KeyboardControllerKeyType::O:return GLFW_KEY_O;
        case KeyboardControllerKeyType::P:return GLFW_KEY_P;

        case KeyboardControllerKeyType::A:return GLFW_KEY_A;
        case KeyboardControllerKeyType::S:return GLFW_KEY_S;
        case KeyboardControllerKeyType::D:return GLFW_KEY_D;
        case KeyboardControllerKeyType::F:return GLFW_KEY_F;
        case KeyboardControllerKeyType::G:return GLFW_KEY_G;
        case KeyboardControllerKeyType::H:return GLFW_KEY_H;
        case KeyboardControllerKeyType::J:return GLFW_KEY_J;
        case KeyboardControllerKeyType::K:return GLFW_KEY_K;
        case KeyboardControllerKeyType::L:return GLFW_KEY_L;

        case KeyboardControllerKeyType::Z:return GLFW_KEY_Z;
        case KeyboardControllerKeyType::X:return GLFW_KEY_X;
        case KeyboardControllerKeyType::C:return GLFW_KEY_C;
        case KeyboardControllerKeyType::V:return GLFW_KEY_V;
        case KeyboardControllerKeyType::B:return GLFW_KEY_B;
        case KeyboardControllerKeyType::N:return GLFW_KEY_N;
        case KeyboardControllerKeyType::M:return GLFW_KEY_M;

        case KeyboardControllerKeyType::UP:return GLFW_KEY_UP;
        case KeyboardControllerKeyType::DOWN:return GLFW_KEY_DOWN;
        case KeyboardControllerKeyType::LEFT:return GLFW_KEY_LEFT;
        case KeyboardControllerKeyType::RIGHT:return GLFW_KEY_RIGHT;

        case KeyboardControllerKeyType::ENTER:return GLFW_KEY_ENTER;
        case KeyboardControllerKeyType::SPACE:return GLFW_KEY_SPACE;
        case KeyboardControllerKeyType::UNKNOWN:
            throw std::invalid_argument("KeyboardControllerKeyType::UNKNOWN");
    }

    throw std::invalid_argument("KeyIFX2GLFW Missing Keys");
}

KeyboardControllerKeyType KeyGLFW2IFX(int glfw_key) {
    switch (glfw_key) {
        case GLFW_KEY_Q:return KeyboardControllerKeyType::Q;
        case GLFW_KEY_W:return KeyboardControllerKeyType::W;
        case GLFW_KEY_E:return KeyboardControllerKeyType::E;
        case GLFW_KEY_R:return KeyboardControllerKeyType::R;
        case GLFW_KEY_T:return KeyboardControllerKeyType::T;
        case GLFW_KEY_Y:return KeyboardControllerKeyType::Y;
        case GLFW_KEY_U:return KeyboardControllerKeyType::U;
        case GLFW_KEY_I:return KeyboardControllerKeyType::I;
        case GLFW_KEY_O:return KeyboardControllerKeyType::O;
        case GLFW_KEY_P:return KeyboardControllerKeyType::P;

        case GLFW_KEY_A:return KeyboardControllerKeyType::A;
        case GLFW_KEY_S:return KeyboardControllerKeyType::S;
        case GLFW_KEY_D:return KeyboardControllerKeyType::D;
        case GLFW_KEY_F:return KeyboardControllerKeyType::F;
        case GLFW_KEY_G:return KeyboardControllerKeyType::G;
        case GLFW_KEY_H:return KeyboardControllerKeyType::H;
        case GLFW_KEY_J:return KeyboardControllerKeyType::J;
        case GLFW_KEY_K:return KeyboardControllerKeyType::K;
        case GLFW_KEY_L:return KeyboardControllerKeyType::L;

        case GLFW_KEY_Z:return KeyboardControllerKeyType::Z;
        case GLFW_KEY_X:return KeyboardControllerKeyType::X;
        case GLFW_KEY_C:return KeyboardControllerKeyType::C;
        case GLFW_KEY_V:return KeyboardControllerKeyType::V;
        case GLFW_KEY_B:return KeyboardControllerKeyType::B;
        case GLFW_KEY_N:return KeyboardControllerKeyType::N;
        case GLFW_KEY_M:return KeyboardControllerKeyType::M;

        case GLFW_KEY_UP:return KeyboardControllerKeyType::UP;
        case GLFW_KEY_DOWN:return KeyboardControllerKeyType::DOWN;
        case GLFW_KEY_LEFT:return KeyboardControllerKeyType::LEFT;
        case GLFW_KEY_RIGHT:return KeyboardControllerKeyType::RIGHT;

        case GLFW_KEY_ENTER:return KeyboardControllerKeyType::ENTER;
        case GLFW_KEY_SPACE:return KeyboardControllerKeyType::SPACE;
        default:return KeyboardControllerKeyType::UNKNOWN;
    }
    throw std::invalid_argument("KeyGLFW2IFX Missing Keys");
}

int KeyboardCallbackIFX2GLFW(KeyboardControllerCallbackType ifx_key) {
    switch (ifx_key) {
        case KeyboardControllerCallbackType::PRESSED:return GLFW_PRESS;
        case KeyboardControllerCallbackType::RELEASED:return GLFW_RELEASE;
        case KeyboardControllerCallbackType::UNKNOWN:
            throw std::invalid_argument(
                "KeyboardControllerCallbackType::UNKNOWN");
    }
    return -1;
}

KeyboardControllerCallbackType KeyboardCallbackGLFW2IFX(int glfw_key) {
    switch (glfw_key) {
        case GLFW_PRESS:return KeyboardControllerCallbackType::PRESSED;
        case GLFW_RELEASE:return KeyboardControllerCallbackType::RELEASED;
        default:return KeyboardControllerCallbackType::UNKNOWN;
    }
}

}