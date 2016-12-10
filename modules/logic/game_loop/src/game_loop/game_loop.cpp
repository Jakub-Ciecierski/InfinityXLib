#include "game_loop/game_loop.h"

#include <rendering/renderer.h>
#include <vr/simulation.h>

namespace ifx {

GameLoop::GameLoop(std::shared_ptr<Renderer> renderer) :
        renderer_(renderer){ }

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
