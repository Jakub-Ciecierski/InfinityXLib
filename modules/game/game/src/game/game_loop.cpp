#include "game/game_loop.h"

#include <graphics/rendering/renderer.h>
#include <physics/physics_simulation.h>
#include <vr/simulation.h>
#include <game/scene_container.h>
#include <controls/controls_events.h>

#include <GLFW/glfw3.h>

namespace ifx {

GameLoop::GameLoop(std::shared_ptr<Renderer> renderer,
                   std::shared_ptr<PhysicsSimulation> physics_simulation,
                   std::shared_ptr<SceneContainer> scene) :
        renderer_(renderer),
        physics_simulation_(physics_simulation),
        scene_(scene){}

GameLoop::~GameLoop(){}

void GameLoop::AddSimulation(std::shared_ptr<Simulation> simulation) {
    simulations_.push_back(simulation);
}

bool GameLoop::RemoveSimulation(std::shared_ptr<Simulation> simulation){
    for(unsigned int i = 0; i < simulations_.size(); i++){
        if(simulations_[i] == simulation){
            simulations_.erase(simulations_.begin() + i);
            return true;
        }
    }
    return false;
}

void GameLoop::Start(){
    while(!renderer_->window()->shouldClose()) {
        renderer_->Render();

        if(!UpdateTime())
            continue;

        physics_simulation_->Update(time_data_.time_delta);
        scene_->Update();
        ControlsEvents::GetInstance().Update();

        for(auto& simulation : simulations_)
            simulation->Update();
    }
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
