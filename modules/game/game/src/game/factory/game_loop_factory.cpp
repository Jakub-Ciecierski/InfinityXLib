#include "game/factory/game_loop_factory.h"

#include <game/game_loop.h>
#include <factory/renderer_factory.h>
#include <physics/factory/physics_simulation_factory.h>

namespace ifx{

GameLoopFactory::GameLoopFactory(){
    renderer_factory_ = std::shared_ptr<RendererFactory>(new RendererFactory());
    physics_simulation_factory
            = std::shared_ptr<PhysicsSimulationFactory>(
            new PhysicsSimulationFactory());
}

GameLoopFactory::~GameLoopFactory(){}

std::shared_ptr<GameLoop> GameLoopFactory::Create(){
    auto game_loop = std::shared_ptr<GameLoop>(
            new GameLoop(
                    renderer_factory_->Create(),
                    physics_simulation_factory->Create()
            ));
    return game_loop;
}

}