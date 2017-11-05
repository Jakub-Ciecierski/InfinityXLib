#include "game/game_loop.h"

#include <graphics/rendering/window/window.h>

#include <game/architecture/engine_architecture.h>
#include <game/game_updater.h>

#include <GLFW/glfw3.h>

namespace ifx {

GameLoop::GameLoop(std::unique_ptr<GameUpdater> game_updater,
                   std::shared_ptr<EngineArchitecture> engine_architecture) :
    game_updater_(std::move(game_updater)),
    engine_architecture_(engine_architecture) {}

void GameLoop::Start() {
    while (!engine_architecture_->window->ShouldClose()) {
        RunSingleIteration();
    }
}

void GameLoop::RunSingleIteration() {
    game_updater_->Update(ComputeElapsedTime());
}

double GameLoop::ComputeElapsedTime(){
    time_data_.current_time = glfwGetTime();

    double elapsed = time_data_.current_time - time_data_.last_time;
    time_data_.total_time += elapsed;
    time_data_.last_time = time_data_.current_time;

    return elapsed;
}


}
