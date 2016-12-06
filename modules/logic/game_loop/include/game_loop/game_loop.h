#ifndef PROJECT_GAME_LOOP_H
#define PROJECT_GAME_LOOP_H

#include <memory>
#include <vector>

namespace ifx {

class Renderer;
class Simulation;

class GameLoop {
public:

    GameLoop(std::shared_ptr<Renderer> renderer);
    ~GameLoop();

    std::shared_ptr<Renderer> renderer(){return renderer_;}

    void AddSimulation(std::shared_ptr<Simulation> simulation);
    void Start();

private:
    std::shared_ptr<Renderer> renderer_;
    std::vector<std::shared_ptr<Simulation>> simulations_;

};
}

#endif //PROJECT_GAME_LOOP_H
