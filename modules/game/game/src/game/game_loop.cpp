#include "game/game_loop.h"

#include <graphics/rendering/renderer.h>

#include <physics/physics_simulation.h>

#include <game/scene_container.h>

#include <controls/controls.h>

#include <gui/gui.h>

#include <GLFW/glfw3.h>

namespace ifx {

GameLoop::GameLoop(const EngineArchitecture& engine_architecture) :
        engine_architecture_(engine_architecture){}

GameLoop::~GameLoop(){}

void GameLoop::Start(){
    while(!engine_architecture_.window->ShouldClose()) {
        RunSingleIteration();
    }
}

void GameLoop::RunSingleIteration(){
    if(!UpdateTime())
        return;

    engine_architecture_.engine_systems.physics_simulation->Update(
            time_data_.time_delta);
    engine_architecture_.engine_systems.scene_container->Update();
    engine_architecture_.engine_systems.renderer->Update();
    engine_architecture_.engine_systems.controls->Update();
    engine_architecture_.engine_systems.gui->Update();

    engine_architecture_.window->Update();
}

bool GameLoop::UpdateTime(){
    time_data_.current_time = glfwGetTime();

    double elapsed = time_data_.current_time - time_data_.last_time;
    time_data_.time_since_last_update += elapsed;
    time_data_.total_time += elapsed;
    time_data_.last_time = time_data_.current_time;

    if(time_data_.time_since_last_update >= time_data_.time_delta){
        time_data_.time_since_last_update = 0.0f;
        return true;
    }
    return false;
}

}
