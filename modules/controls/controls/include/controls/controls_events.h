#ifndef PROJECT_CONTROLS_EVENTS_H
#define PROJECT_CONTROLS_EVENTS_H

#include <controls/mouse_event.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace ifx {

using Keys = std::vector<bool>;

class ControlsEvents {
public:
    ~ControlsEvents();

    static ControlsEvents& GetInstance();

    const Keys& keyboard_keys() {return keyboard_keys_;}
    MouseEvents& mouse_events() {return mouse_events_;}

    void OnKeyboardEvent(int action, int key);
    void OnMouseButtonEvent(MouseButtonType type, bool is_pressed,
                            float xpos, float ypos);
    void OnMouseEvent(float xpos, float ypos);
    void OnMouseScrollEvent(float xoffset, float yoffset);

    /**
     * Must be called after all EventHandlers were called.
     */
    void Update();

private:
    ControlsEvents();

    Keys keyboard_keys_;
    MouseEvents mouse_events_;
};

}

#endif // PROJECT_CONTROLS_EVENTS_H
