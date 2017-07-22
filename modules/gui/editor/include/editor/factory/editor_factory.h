#ifndef PROJECT_ENGINE_GUI_FACTORY_H
#define PROJECT_ENGINE_GUI_FACTORY_H

#include <memory>

namespace ifx {

class Editor;
class MainMenu;
class Renderer;
class SceneView;
class SceneContainer;
class PhysicsSimulation;
class PhysicsSimulationView;
class ImGuiDemoView;
class ResourceContext;
class Window;
class Docker;
class View;

class EditorFactory {
public:
    EditorFactory();
    ~EditorFactory();

    std::shared_ptr<Editor> CreateEngineGUI(
            std::shared_ptr<Window> window,
            std::shared_ptr<SceneContainer> scene,
            std::shared_ptr<PhysicsSimulation> physics_simulation,
            std::shared_ptr<ResourceContext> resource_creator);
private:
    std::shared_ptr<SceneView> CreateSceneView(
            std::shared_ptr<SceneContainer> scene,
            std::shared_ptr<ResourceContext> resource_creator);
    std::shared_ptr<PhysicsSimulationView> CreatePhysicsSimulationView(
            std::shared_ptr<PhysicsSimulation> physics_simulation);

    std::shared_ptr<Docker> CreateDefaultDocker(
            std::shared_ptr<Window> window,
            std::shared_ptr<View> scene_view,
            std::shared_ptr<View> physics_view,
            std::shared_ptr<View>main_menu_view,
            std::shared_ptr<View> imgui_demo);
};

}

#endif //PROJECT_ENGINE_GUI_FACTORY_H
