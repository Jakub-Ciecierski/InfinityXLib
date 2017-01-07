#ifndef PROJECT_EXAMPLE_GUI_H
#define PROJECT_EXAMPLE_GUI_H

#include "gui/gui.h"

#include <memory>

namespace ifx{
class EngineGUI;
class SceneContainer;
}

class ExampleGUI : public ifx::GUI{
public:

    ExampleGUI(GLFWwindow* window,
               std::shared_ptr<ifx::SceneContainer> scene);
    ~ExampleGUI();

    virtual void Render() override;
private:
    std::shared_ptr<ifx::EngineGUI> engine_gui_;

};


#endif //PROJECT_EXAMPLE_GUI_H
