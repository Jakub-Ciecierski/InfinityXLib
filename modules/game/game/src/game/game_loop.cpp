#include "game/game_loop.h"

#include <graphics/rendering/renderer.h>

#include <physics/physics_simulation.h>

#include <game/scene_container.h>

#include <controls/controls.h>

#include <gui/gui.h>

#include <GLFW/glfw3.h>

namespace ifx {

GameLoop::GameLoop(std::shared_ptr<Renderer> renderer,
                   std::shared_ptr<PhysicsSimulation> physics_simulation,
                   std::shared_ptr<Controls> controls,
                   std::shared_ptr<SceneContainer> scene,
                   std::shared_ptr<GUI> gui) :
        renderer_(renderer),
        physics_simulation_(physics_simulation),
        controls_(controls),
        scene_(scene),
        gui_(gui){}

GameLoop::~GameLoop(){}

void GameLoop::Start(){
    while(!renderer_->window()->ShouldClose()) {
        RunSingleIteration();
    }
}

void GameLoop::RunSingleIteration(){
    if(!UpdateTime())
        return;

    physics_simulation_->Update(time_data_.time_delta);
    scene_->Update();
    renderer_->Update();
    controls_->Update();

    gui_->Update();

    // Window must be last
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
