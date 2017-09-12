#ifndef PROJECT_INPUT_TYPES_H
#define PROJECT_INPUT_TYPES_H

namespace ifx {

enum class KeyboardControllerKeyType {
    Q, W, E, R, T, Y, U, I, O, P, A, S, D,
    F, G, H, J, K, L, Z, X, C, V, B, N, M,
    UP, DOWN, LEFT, RIGHT,
    SPACE, ENTER,

    UNKNOWN,
};

enum class KeyboardControllerCallbackType {
    PRESSED, RELEASED,

    UNKNOWN,
};

struct KeyboardControllerEventType {
    KeyboardControllerKeyType key;
    KeyboardControllerCallbackType callback;
};

enum class MouseControllerKeyType {
    MOUSE_LEFT, MOUSE_RIGHT,
    MOUSE_MIDDLE, MOUSE_SCROLL,

    UNKNOWN,
};

enum class MouseControllerCallbackType {
    PRESSED, RELEASED, SCROLL_ACTIVE,

    UNKNOWN,
};

struct MouseControllerEventType {
    MouseControllerKeyType key;
    MouseControllerCallbackType callback;
};

}

#endif //PROJECT_INPUT_TYPES_H
