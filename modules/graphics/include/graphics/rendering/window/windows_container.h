#ifndef PROJECT_WINDOWS_CONTAINER_H
#define PROJECT_WINDOWS_CONTAINER_H

#include <vector>

struct GLFWwindow;

namespace ifx {

class Window;

class WindowsContainer {
public:
    ~WindowsContainer();

    static WindowsContainer& GetInstance();

    void AddWindow(Window* window);
    Window* GetWindow(GLFWwindow* glfw_window);
private:
    std::vector<Window*> windows_;
    WindowsContainer();
};
}

#endif //PROJECT_WINDOWS_CONTAINER_H
