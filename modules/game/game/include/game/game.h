#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include <memory>

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
         std::shared_ptr<SceneContainer> scene,
         std::shared_ptr<ResourceContext> resource_creator,
         std::shared_ptr<RenderingContext> rendering_context_);
    ~Game();

    std::shared_ptr<GameLoop> game_loop() {return game_loop_;}
    std::shared_ptr<SceneContainer> scene() {return scene_;}
    std::shared_ptr<ResourceContext> resource_creator() {
        return resource_creator_;}

    void Start();
private:
    void Terminate();

    std::shared_ptr<RenderingContext> rendering_context_;

    std::shared_ptr<ResourceContext> resource_creator_;

    std::shared_ptr<GameLoop> game_loop_;

    std::shared_ptr<SceneContainer> scene_;

};
}

#endif //PROJECT_GAME_H
