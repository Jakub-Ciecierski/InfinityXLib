#include "game/game_loop.h"

#include <graphics/rendering/window/window.h>

#include <GLFW/glfw3.h>

namespace ifx {

GameLoop::GameLoop(std::unique_ptr<GameUpdater> game_updater){
    game_updater_ = game_updater.get();
    game_updaters_.push_back(std::move(game_updater));
}

void GameLoop::AddGameUpdater(std::unique_ptr<GameUpdater> game_updater){
    game_updaters_.push_back(std::move(game_updater));
}

void GameLoop::Start() {
    while (!game_updater_->engine_architecture()->window->ShouldClose()) {
        RunSingleIteration();
    }
}

void GameLoop::RunSingleIteration() {
    auto elapsed_time = ComputeElapsedTime();

    for(auto& game_updater : game_updaters_){
        game_updater->Update(elapsed_time);
    }
}

double GameLoop::ComputeElapsedTime(){
    time_data_.current_time = glfwGetTime();

    double elapsed = time_data_.current_time - time_data_.last_time;
    time_data_.total_time += elapsed;
    time_data_.last_time = time_data_.current_time;

    return elapsed;
}


}
