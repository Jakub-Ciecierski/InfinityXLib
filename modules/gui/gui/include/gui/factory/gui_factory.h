#ifndef PROJECT_GUI_FACTORY_H
#define PROJECT_GUI_FACTORY_H

#include <memory>
#include <vector>

namespace ifx {

class GUI;
class GUIContext;
class GUIPart;

class GUIFactory {
public:

    GUIFactory();

    ~GUIFactory();

    std::shared_ptr<GUI> Create(std::shared_ptr<GUIContext> context);
private:

};
}


#endif //PROJECT_GUI_FACTORY_H
