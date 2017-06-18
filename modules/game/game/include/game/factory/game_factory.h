#ifndef PROJECT_GAME_FACTORY_H
#define PROJECT_GAME_FACTORY_H

#include <memory>

namespace ifx {

class Game;
class GameLoopFactory;
class SceneContainerFactory;
class RendererFactory;
class PhysicsSimulationFactory;

class GameFactory {
public:

    GameFactory();
    ~GameFactory();

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
    std::shared_ptr<GameLoopFactory> game_loop_factory_;
    std::shared_ptr<SceneContainerFactory> scene_factory_;
    std::shared_ptr<RendererFactory> renderer_factory_;
    std::shared_ptr<PhysicsSimulationFactory> physics_simulation_factory_;

};
}

#endif //PROJECT_GAME_FACTORY_H
