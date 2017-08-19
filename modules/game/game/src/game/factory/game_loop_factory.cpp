#include "game/factory/game_loop_factory.h"

#include <game/game_loop.h>
#include <graphics/factory/renderer_factory.h>
#include <physics/factory/bullet_physics_simulation_factory.h>

namespace ifx {

GameLoopFactory::GameLoopFactory(){}
GameLoopFactory::~GameLoopFactory(){}

std::shared_ptr<GameLoop> GameLoopFactory::Create(
        const EngineArchitecture& engine_architecture){
    auto game_loop = std::shared_ptr<GameLoop>(
            new GameLoop(engine_architecture));
    return game_loop;
}

}