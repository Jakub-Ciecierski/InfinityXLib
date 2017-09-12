#ifndef PROJECT_CONTROLS_CONTAINER_H
#define PROJECT_CONTROLS_CONTAINER_H

namespace ifx {

class Controls;

/**
 * Ugly static hack to fetch controls in native GLFW callbacks
 */
class ControlsContainer {
public:
    static ControlsContainer &GetInstance();

    ~ControlsContainer();

    Controls *controls() { return controls_; }
    void controls(Controls *controls) { controls_ = controls; }

private:
    ControlsContainer();

    Controls *controls_;
};
}

#endif //PROJECT_CONTROLS_CONTAINER_H
