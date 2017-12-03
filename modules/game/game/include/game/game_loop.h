#ifndef PROJECT_GAME_LOOP_H
#define PROJECT_GAME_LOOP_H

#include <memory>
#include <vector>

#include <game/architecture/engine_architecture.h>
#include <game/game_updater.h>

namespace ifx {

class Renderer;
class PhysicsSimulation;
class SceneContainer;
class Controls;
class GUI;

class GameUpdater;

struct GameTimeData {
    float last_time = 0;
    float current_time = 0;

    float total_time = 0;

    float time_since_last_update = 0;
    const float time_delta = 1.0f / 60.0f;
};

class GameLoop {
public:
    GameLoop(std::unique_ptr<GameUpdater> game_updater);
    ~GameLoop() = default;

    std::shared_ptr<Renderer> renderer() {
        return
            game_updater_->engine_architecture()->engine_systems.renderer;
    }
    std::shared_ptr<PhysicsSimulation> physics_simulation() {
        return
            game_updater_->engine_architecture()->engine_systems
                .physics_simulation;
    }
    std::shared_ptr<Controls> controls() {
        return
            game_updater_->engine_architecture()->engine_systems.controls;
    };
    std::shared_ptr<GUI> gui() {
        return game_updater_->engine_architecture()->engine_systems.gui;
    }

    const std::vector<std::unique_ptr<GameUpdater>>& game_updaters(){
        return game_updaters_;
    };

    void AddGameUpdater(std::unique_ptr<GameUpdater> game_updater);

    void Start();
private:
    void RunSingleIteration();

    double ComputeElapsedTime();

    GameUpdater* game_updater_;

    std::vector<std::unique_ptr<GameUpdater>> game_updaters_;

    GameTimeData time_data_;
};
}

#endif //PROJECT_GAME_LOOP_H
