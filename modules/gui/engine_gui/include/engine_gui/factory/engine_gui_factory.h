#ifndef PROJECT_ENGINE_GUI_FACTORY_H
#define PROJECT_ENGINE_GUI_FACTORY_H

#include <memory>

namespace ifx {

class EngineGUI;
class MainMenu;
class Renderer;
class SceneView;
class SceneContainer;
class PhysicsSimulation;
class PhysicsSimulationView;
class ImGuiDemoView;
class ResourceContext;

class EngineGUIFactory {
public:
    EngineGUIFactory();
    ~EngineGUIFactory();

    std::shared_ptr<EngineGUI> CreateEngineGUI(
            std::shared_ptr<SceneContainer> scene,
            std::shared_ptr<PhysicsSimulation> physics_simulation,
            std::shared_ptr<ResourceContext> resource_creator);
private:
    std::shared_ptr<SceneView> CreateSceneView(
            std::shared_ptr<SceneContainer> scene,
            std::shared_ptr<ResourceContext> resource_creator);
    std::shared_ptr<PhysicsSimulationView> CreatePhysicsSimulationView(
            std::shared_ptr<PhysicsSimulation> physics_simulation);
    std::shared_ptr<MainMenu> CreateMainMenu(
            std::shared_ptr<SceneView> scene_view,
            std::shared_ptr<PhysicsSimulationView> physics_simulation_view,
            std::shared_ptr<ImGuiDemoView> imgui_demo_view);
};

}

#endif //PROJECT_ENGINE_GUI_FACTORY_H
