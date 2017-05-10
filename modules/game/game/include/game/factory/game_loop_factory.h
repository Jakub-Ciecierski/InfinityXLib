#ifndef PROJECT_GAME_LOOP_FACTORY_H
#define PROJECT_GAME_LOOP_FACTORY_H

#include <memory>

namespace ifx {

class Renderer;
class PhysicsSimulation;
class GameLoop;
class SceneContainer;
class Controls;

class GameLoopFactory {
public:

    GameLoopFactory();
    ~GameLoopFactory();

    std::shared_ptr<GameLoop> Create(
            std::shared_ptr<Renderer> renderer,
            std::shared_ptr<PhysicsSimulation> physics_simulation,
            std::shared_ptr<Controls> controls,
            std::shared_ptr<SceneContainer> scene);
private:
};
}

#endif //PROJECT_GAME_LOOP_FACTORY_H
