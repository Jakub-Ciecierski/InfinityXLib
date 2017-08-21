#ifndef PROJECT_WINDOW_OBSERVER_H
#define PROJECT_WINDOW_OBSERVER_H

namespace ifx {

class WindowObserver {
public:
    WindowObserver() = default;
    ~WindowObserver() = default;

    virtual void OnResize(int width, int height) = 0;
};
}

#endif //PROJECT_WINDOW_OBSERVER_H
