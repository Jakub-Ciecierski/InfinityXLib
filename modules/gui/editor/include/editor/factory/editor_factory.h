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

struct EngineArchitecture;

class EditorFactory {
public:
    EditorFactory() = default;
    ~EditorFactory() = default;

    std::shared_ptr<Editor> CreateEngineGUI(
            std::shared_ptr<EngineArchitecture> engine_architecture);
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
    std::shared_ptr<WindowView> CreateSoftBodyWindowView(
            std::shared_ptr<EngineArchitecture> engine_architecture);

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
            std::shared_ptr<WindowView> left_window_view,
            std::shared_ptr<WindowView> right_window_view,
            std::shared_ptr<WindowView> top_window_view,
            std::shared_ptr<WindowView> bottom_window_view,
            std::shared_ptr<WindowView> soft_body_window_view);
};

}

#endif //PROJECT_ENGINE_GUI_FACTORY_H
