#ifndef PROJECT_WINDOW_FACTORY_H
#define PROJECT_WINDOW_FACTORY_H

#include <memory>

namespace ifx {

class Window;

class WindowFactory {
public:
    WindowFactory(std::string name = "InfinityX",
                  int width = 1200, int height = 800);

    ~WindowFactory();

    std::shared_ptr<Window> Create();

private:
    std::string name_;
    int width_;
    int height_;

};
}


#endif //PROJECT_WINDOW_FACTORY_H
