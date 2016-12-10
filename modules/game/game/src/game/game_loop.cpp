#include "game/game_loop.h"

#include <rendering/renderer.h>
#include <physics/physics_simulation.h>
#include <vr/simulation.h>

namespace ifx {

GameLoop::GameLoop(std::shared_ptr<Renderer> renderer,
                   std::shared_ptr<PhysicsSimulation> physics_simulation) :
        renderer_(renderer),
        physics_simulation_(physics_simulation){ }

GameLoop::~GameLoop(){

}

void GameLoop::AddSimulation(std::shared_ptr<Simulation> simulation) {
    simulations_.push_back(simulation);
}

void GameLoop::Start(){
    while(!renderer_->window()->shouldClose()) {
        renderer_->HandleEvents();
        renderer_->Update();
        renderer_->Render();

        for(auto& simulation : simulations_)
            simulation->Update();
    }

    renderer_->window()->Terminate();
}
}
