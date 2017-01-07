#ifndef PROJECT_ENGINE_GUI_FACTORY_H
#define PROJECT_ENGINE_GUI_FACTORY_H

#include <memory>

namespace ifx {

class EngineGUI;
class MainMenu;
class Renderer;
class SceneView;
class SceneContainer;

class EngineGUIFactory {
public:
    EngineGUIFactory();
    ~EngineGUIFactory();

    std::shared_ptr<EngineGUI> CreateEngineGUI(
            std::shared_ptr<SceneContainer> scene);
private:
    std::shared_ptr<MainMenu> CreateMainMenu();
    std::shared_ptr<SceneView> CreateSceneView(
            std::shared_ptr<SceneContainer> scene);
};

}

#endif //PROJECT_ENGINE_GUI_FACTORY_H
