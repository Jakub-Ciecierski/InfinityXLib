#ifndef PROJECT_WINDOW_SUBJECT_H
#define PROJECT_WINDOW_SUBJECT_H

#include <vector>

namespace ifx {

class WindowObserver;

/**
 * Part of the Window Observer pattern
 */
class WindowSubject {
public:
    WindowSubject() = default;
    ~WindowSubject() = default;

    void NotifyResize(int width, int height);

    void AddObserver(WindowObserver* observer);
    bool RemoveObserver(WindowObserver* observer);

protected:
    std::vector<WindowObserver*> observers_;
};
}

#endif //PROJECT_WINDOW_SUBJECT_H
