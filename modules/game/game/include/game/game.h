#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include <memory>
#include <game/architecture/engine_architecture.h>

namespace ifx {

class GameLoop;
class SceneContainer;
class ResourceContext;
class RenderingContext;

/**
 * Game is responsible for maintaining the game loop and all its requirements
 * (e.g. renderer, physics simulation, control system etc.).
 */
class Game {
public:

    Game(std::shared_ptr<GameLoop> game_loop,
         const EngineArchitecture& engine_architecture);
    ~Game();

    std::shared_ptr<GameLoop> game_loop() {return game_loop_;}
    std::shared_ptr<SceneContainer> scene() {
            return engine_architecture_.engine_systems.scene_container;}
    std::shared_ptr<ResourceContext> resource_creator() {
        return engine_architecture_.engine_contexts.resource_context;}

    void Start();
private:
    void Terminate();

    std::shared_ptr<GameLoop> game_loop_;

    EngineArchitecture engine_architecture_;

};
}

#endif //PROJECT_GAME_H
