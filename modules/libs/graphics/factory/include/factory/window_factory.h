#ifndef IFX_WINDOW_FACTORY_H
#define IFX_WINDOW_FACTORY_H

namespace ifx{

class Window;

class WindowFactory {
public:
    WindowFactory();
    ~WindowFactory();

    std::shared_ptr<Window> Create(WindowCreateParams params);
private:
};

}

#endif //IFX_WINDOW_FACTORY_H
