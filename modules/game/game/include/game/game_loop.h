#ifndef PROJECT_GAME_LOOP_H
#define PROJECT_GAME_LOOP_H

#include <memory>
#include <vector>

namespace ifx {

class Renderer;
class PhysicsSimulation;
class Simulation;
class SceneContainer;

class GameLoop {
public:
    GameLoop(std::shared_ptr<Renderer> renderer,
             std::shared_ptr<PhysicsSimulation> physics_simulation,
             std::shared_ptr<SceneContainer> scene);
    ~GameLoop();

    std::shared_ptr<Renderer> renderer(){return renderer_;}
    std::shared_ptr<PhysicsSimulation>
    physics_simulation(){return physics_simulation_;}

    void AddSimulation(std::shared_ptr<Simulation> simulation);
    void Start();

private:
    std::shared_ptr<Renderer> renderer_;
    std::shared_ptr<PhysicsSimulation> physics_simulation_;

    std::shared_ptr<SceneContainer> scene_;

    std::vector<std::shared_ptr<Simulation>> simulations_;

};
}

#endif //PROJECT_GAME_LOOP_H
