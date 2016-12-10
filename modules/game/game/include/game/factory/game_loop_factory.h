#ifndef PROJECT_GAME_LOOP_FACTORY_H
#define PROJECT_GAME_LOOP_FACTORY_H

#include <memory>

namespace ifx {

class PhysicsSimulationFactory;
class RendererFactory;
class GameLoop;

class GameLoopFactory {
public:

    GameLoopFactory();
    ~GameLoopFactory();

    std::shared_ptr<GameLoop> Create();
private:

    std::shared_ptr<RendererFactory> renderer_factory_;
    std::shared_ptr<PhysicsSimulationFactory> physics_simulation_factory;
};
}

#endif //PROJECT_GAME_LOOP_FACTORY_H
