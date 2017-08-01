#ifndef PROJECT_ENGINE_GUI_FACTORY_H
#define PROJECT_ENGINE_GUI_FACTORY_H

#include <memory>

namespace ifx {

class Editor;
class MainMenuWindowView;
class Renderer;
class SceneView;
class SceneContainer;
class PhysicsSimulation;
class RightView;
class ImGuiDemoWindowView;
class ResourceContext;
class Window;
class Docker;
class WindowView;
class PhysicsSimulationView;
class SceneRenderer;
class RenderingView;

class EditorFactory {
public:
    EditorFactory();
    ~EditorFactory();

    std::shared_ptr<Editor> CreateEngineGUI(
            std::shared_ptr<Window> window,
            std::shared_ptr<SceneContainer> scene,
            std::shared_ptr<PhysicsSimulation> physics_simulation,
            std::shared_ptr<SceneRenderer> scene_renderer,
            std::shared_ptr<ResourceContext> resource_creator);
private:
    std::shared_ptr<WindowView> CreateLeftWindowView(
            std::shared_ptr<SceneContainer> scene,
            std::shared_ptr<ResourceContext> resource_creator,
            std::shared_ptr<SceneRenderer> scene_renderer);
    std::shared_ptr<WindowView> CreateRightWindowView(
            std::shared_ptr<SceneRenderer> scene_renderer,
            std::shared_ptr<ResourceContext> resource_creator,
            std::shared_ptr<PhysicsSimulation> physics_simulation);
    std::shared_ptr<WindowView> CreateBottomWindowView();

    std::shared_ptr<SceneView> CreateSceneView(
            std::shared_ptr<SceneContainer> scene,
            std::shared_ptr<ResourceContext> resource_creator,
            std::shared_ptr<SceneRenderer> scene_renderer);
    std::shared_ptr<PhysicsSimulationView> CreatePhysicsSimulationView(
            std::shared_ptr<PhysicsSimulation> physics_simulation);

    std::shared_ptr<RenderingView> CreateRenderingView(
            std::shared_ptr<SceneRenderer> scene_renderer,
            std::shared_ptr<ResourceContext> resource_creator);

    std::shared_ptr<Docker> CreateDefaultDocker(
            std::shared_ptr<Window> window,
            std::shared_ptr<WindowView> scene_view,
            std::shared_ptr<WindowView> physics_view,
            std::shared_ptr<WindowView>main_menu_view,
            std::shared_ptr<WindowView> imgui_demo);
};

}

#endif //PROJECT_ENGINE_GUI_FACTORY_H
