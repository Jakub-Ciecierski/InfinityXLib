#ifndef PROJECT_GAME_LOOP_H
#define PROJECT_GAME_LOOP_H

#include <memory>
#include <vector>

#include <game/architecture/engine_architecture.h>

namespace ifx {

class Renderer;
class PhysicsSimulation;
class SceneContainer;
class Controls;
class GUI;

class GameUpdater;

struct EngineArchitecture;

struct GameTimeData {
    float last_time = 0;
    float current_time = 0;

    float total_time = 0;

    float time_since_last_update = 0;
    const float time_delta = 1.0f / 60.0f;
};

class GameLoop {
public:
    GameLoop(std::unique_ptr<GameUpdater> game_updater,
             std::shared_ptr<EngineArchitecture> engine_architecture);
    ~GameLoop() = default;

    std::shared_ptr<Renderer> renderer() {
        return
            engine_architecture_->engine_systems.renderer;
    }
    std::shared_ptr<PhysicsSimulation> physics_simulation() {
        return engine_architecture_->engine_systems.physics_simulation;
    }
    std::shared_ptr<Controls> controls() {
        return
            engine_architecture_->engine_systems.controls;
    };
    std::shared_ptr<GUI> gui() {
        return engine_architecture_->engine_systems.gui;
    }

    void Start();
private:
    void RunSingleIteration();

    double ComputeElapsedTime();

    std::unique_ptr<GameUpdater> game_updater_;

    std::shared_ptr<EngineArchitecture> engine_architecture_;

    GameTimeData time_data_;
};
}

#endif //PROJECT_GAME_LOOP_H
