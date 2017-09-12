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

GameLoop::~GameLoop() {}

void GameLoop::Start() {
    while (!engine_architecture_->window->ShouldClose()) {
        RunSingleIteration();
    }
}

void GameLoop::RunSingleIteration() {
    if (!UpdateTime())
        return;
    game_updater_->Update(time_data_.time_delta);
}

bool GameLoop::UpdateTime() {
    time_data_.current_time = glfwGetTime();

    double elapsed = time_data_.current_time - time_data_.last_time;
    time_data_.time_since_last_update += elapsed;
    time_data_.total_time += elapsed;
    time_data_.last_time = time_data_.current_time;

    if (time_data_.time_since_last_update >= time_data_.time_delta) {
        time_data_.time_since_last_update = 0.0f;
        return true;
    }
    return false;
}

}
