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
         std::shared_ptr<EngineArchitecture> engine_architecture);
    ~Game() = default;

    std::shared_ptr<GameLoop> game_loop() {return game_loop_;}
    std::shared_ptr<SceneContainer> scene() {
            return engine_architecture_->engine_systems.scene_container;}
    std::shared_ptr<ResourceContext> resource_context() {
        return engine_architecture_->engine_contexts.resource_context;}

    std::shared_ptr<EngineArchitecture> engine_architecture(){
        return engine_architecture_; }

    void Start();
private:
    void Terminate();
    void TerminateSystems();
    void TerminateContexts();

    std::shared_ptr<GameLoop> game_loop_;

    std::shared_ptr<EngineArchitecture> engine_architecture_;

};
}

#endif //PROJECT_GAME_H
