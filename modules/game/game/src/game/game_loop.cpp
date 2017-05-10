#include "game/game_loop.h"

#include <graphics/rendering/renderer.h>

#include <physics/physics_simulation.h>

#include <game/scene_container.h>

#include <controls/controls_events.h>
#include <controls/controls.h>

#include <GLFW/glfw3.h>

namespace ifx {

GameLoop::GameLoop(std::shared_ptr<Renderer> renderer,
                   std::shared_ptr<PhysicsSimulation> physics_simulation,
                   std::shared_ptr<Controls> controls,
                   std::shared_ptr<SceneContainer> scene) :
        renderer_(renderer),
        physics_simulation_(physics_simulation),
        controls_(controls),
        scene_(scene){}

GameLoop::~GameLoop(){}

void GameLoop::Start(){
    while(!renderer_->window()->ShouldClose()) {
        RunSingleIteration();
    }
}

void GameLoop::RunSingleIteration(){
    if(!UpdateTime())
        return;

    renderer_->Update();

    physics_simulation_->Update(time_data_.time_delta);

    controls_->Update();

    scene_->Update();

    renderer_->window()->Update();
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
