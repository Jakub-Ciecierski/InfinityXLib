#ifndef PROJECT_ENGINE_GUI_FACTORY_H
#define PROJECT_ENGINE_GUI_FACTORY_H

#include <memory>

namespace ifx {

class EngineGUI;
class MainMenu;
class Renderer;
class SceneView;
class Scene;

class EngineGUIFactory {
public:
    EngineGUIFactory();
    ~EngineGUIFactory();

    std::shared_ptr<EngineGUI> CreateEngineGUI(std::shared_ptr<Renderer> renderer);
private:
    std::shared_ptr<MainMenu> CreateMainMenu();
    std::shared_ptr<SceneView> CreateSceneView(std::shared_ptr<Scene> scene);
};

}

#endif //PROJECT_ENGINE_GUI_FACTORY_H
