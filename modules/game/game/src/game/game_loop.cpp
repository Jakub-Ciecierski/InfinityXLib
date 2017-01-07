#include "game/game_loop.h"

#include <graphics/rendering/renderer.h>
#include <physics/physics_simulation.h>
#include <vr/simulation.h>
#include <game/scene_container.h>
#include <controls/controls_events.h>

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

void GameLoop::Start(){
    while(!renderer_->window()->shouldClose()) {
        renderer_->Render();
        physics_simulation_->Update();
        scene_->Update();
        ControlsEvents::GetInstance().Update();

        for(auto& simulation : simulations_)
            simulation->Update();
    }
}
}
