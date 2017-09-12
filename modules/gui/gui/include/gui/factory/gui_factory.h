#ifndef PROJECT_GUI_FACTORY_H
#define PROJECT_GUI_FACTORY_H

#include <memory>
#include <vector>

namespace ifx {

class GUI;
class GUIContext;
class GUIPart;
class ControlContext;

class GUIFactory {
public:

    GUIFactory() = default;
    ~GUIFactory() = default;

    std::shared_ptr<GUI> Create(std::shared_ptr<GUIContext> context);

private:

};
}

#endif //PROJECT_GUI_FACTORY_H
