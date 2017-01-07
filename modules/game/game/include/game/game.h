#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include <memory>

namespace ifx {

class GameLoop;
class SceneContainer;

/**
 * Game is responsible for maintaining the game loop and all its requirements
 * (e.g. renderer, physics simulation, control system etc.).
 */
class Game {
public:

    Game(std::shared_ptr<GameLoop> game_loop,
         std::shared_ptr<SceneContainer> scene);
    ~Game();

    std::shared_ptr<GameLoop> game_loop() {return game_loop_;}
    std::shared_ptr<SceneContainer> scene() {return scene_;}

    void Start();
private:
    std::shared_ptr<GameLoop> game_loop_;
    std::shared_ptr<SceneContainer> scene_;
};
}

#endif //PROJECT_GAME_H
