#ifndef PROJECT_GAME_LOOP_FACTORY_H
#define PROJECT_GAME_LOOP_FACTORY_H

#include <memory>

namespace ifx {

class Renderer;
class PhysicsSimulation;
class GameLoop;
class SceneContainer;
class Controls;
class GUI;

struct EngineArchitecture;

class GameLoopFactory {
public:

    GameLoopFactory();
    ~GameLoopFactory();

    std::shared_ptr<GameLoop> Create(
            const EngineArchitecture& engine_architecture);
private:
};
}

#endif //PROJECT_GAME_LOOP_FACTORY_H
