#ifndef PROJECT_GAME_FACTORY_H
#define PROJECT_GAME_FACTORY_H

#include <memory>

namespace ifx {

class Game;
class GameLoopFactory;
class SceneContainerFactory;
class RendererFactory;
class PhysicsSimulationFactory;
class ResourceContextFactory;
class RenderingContextFactory;
class WindowFactory;
class ControlsFactory;
class ControlContextFactory;
class GUIContextFactory;
class GUIFactory;
class Window;

struct EngineContexts;
struct EngineSystems;
struct EngineArchitecture;

class GameFactory {
public:

    GameFactory();
    ~GameFactory();

    GameFactory& SetWindowFactory(
            std::shared_ptr<WindowFactory> factory);
    GameFactory& SetRenderingContextFactory(
            std::shared_ptr<RenderingContextFactory> factory);
    GameFactory& SetResourceContextFactory(
            std::shared_ptr<ResourceContextFactory> factory);
    GameFactory& SetGameLoopFactory(
            std::shared_ptr<GameLoopFactory> game_loop_factory);
    GameFactory& SetSceneContainerFactory(
            std::shared_ptr<SceneContainerFactory> scene_factory);
    GameFactory& SetRendererFactory(
            std::shared_ptr<RendererFactory> renderer_factory);
    GameFactory& SetPhysicsSimulationFactory(
            std::shared_ptr<PhysicsSimulationFactory>
            physics_simulation_factory);
    GameFactory& SetControlsFactory(std::shared_ptr<ControlsFactory> factory);
    GameFactory& SetControlContextFactory(
            std::shared_ptr<ControlContextFactory> factory);

    GameFactory& SetGUIContextFactory(
            std::shared_ptr<GUIContextFactory> factory);
    GameFactory& SetGUIFactory(
            std::shared_ptr<GUIFactory> factory);

    std::shared_ptr<Game> Create();
private:
    void CreateDefaultFactories();

    EngineContexts CreateEngineContexts();
    std::shared_ptr<Window> CreateWindow(const EngineContexts& engine_contexts);
    EngineSystems CreateEngineSystems(std::shared_ptr<Window> window,
                                      const EngineContexts& engine_contexts);

    std::shared_ptr<RenderingContextFactory> rendering_context_factory_;
    std::shared_ptr<ResourceContextFactory> resource_context_factory_;
    std::shared_ptr<ControlContextFactory> control_context_factory_;
    std::shared_ptr<GUIContextFactory> gui_context_factory_;

    std::shared_ptr<WindowFactory> window_factory_;

    std::shared_ptr<RendererFactory> renderer_factory_;
    std::shared_ptr<PhysicsSimulationFactory> physics_simulation_factory_;
    std::shared_ptr<ControlsFactory> controls_factory_;
    std::shared_ptr<SceneContainerFactory> scene_factory_;
    std::shared_ptr<GUIFactory> gui_factory_;

    std::shared_ptr<GameLoopFactory> game_loop_factory_;

};
}

#endif //PROJECT_GAME_FACTORY_H
