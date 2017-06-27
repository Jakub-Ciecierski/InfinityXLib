#ifndef PROJECT_GAME_LOOP_H
#define PROJECT_GAME_LOOP_H

#include <memory>
#include <vector>

namespace ifx {

class Renderer;
class PhysicsSimulation;
class SceneContainer;
class Controls;
class GUI;

struct GameTimeData{
    float last_time = 0;
    float current_time = 0;

    float total_time = 0;

    float time_since_last_update = 0;
    const float time_delta = 1.0f / 60.0f;
};

class GameLoop {
public:
    GameLoop(std::shared_ptr<Renderer> renderer,
             std::shared_ptr<PhysicsSimulation> physics_simulation,
             std::shared_ptr<Controls> controls,
             std::shared_ptr<SceneContainer> scene,
             std::shared_ptr<GUI> gui);
    ~GameLoop();

    std::shared_ptr<Renderer> renderer(){return renderer_;}
    std::shared_ptr<PhysicsSimulation>
    physics_simulation(){return physics_simulation_;}
    std::shared_ptr<Controls> controls(){return controls_;};

    std::shared_ptr<GUI> gui(){return gui_;}

    void Start();
private:
    void RunSingleIteration();

    bool UpdateTime();

    std::shared_ptr<Renderer> renderer_;
    std::shared_ptr<PhysicsSimulation> physics_simulation_;
    std::shared_ptr<Controls> controls_;

    std::shared_ptr<SceneContainer> scene_;

    std::shared_ptr<GUI> gui_;

    GameTimeData time_data_;
};
}

#endif //PROJECT_GAME_LOOP_H
