#ifndef PROJECT_MOUSE_INPUT_FACTORY_H
#define PROJECT_MOUSE_INPUT_FACTORY_H

#include <memory>

namespace ifx {

class MouseController;

class MouseControllerFactory {
public:

    MouseControllerFactory();
    ~MouseControllerFactory();

    std::shared_ptr<MouseController> Create();

private:
};
}

#endif //PROJECT_MOUSE_INPUT_FACTORY_H
