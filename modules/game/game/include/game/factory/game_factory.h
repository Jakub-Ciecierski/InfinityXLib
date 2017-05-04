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


    std::shared_ptr<Game> Create();
private:
    void CreateDefaultFactories();

    std::shared_ptr<RenderingContextFactory> rendering_context_factory_;
    std::shared_ptr<ResourceContextFactory> resource_context_factory_;

    std::shared_ptr<WindowFactory> window_factory_;
    std::shared_ptr<RendererFactory> renderer_factory_;

    std::shared_ptr<PhysicsSimulationFactory> physics_simulation_factory_;

    std::shared_ptr<SceneContainerFactory> scene_factory_;

    std::shared_ptr<GameLoopFactory> game_loop_factory_;

};
}

#endif //PROJECT_GAME_FACTORY_H
