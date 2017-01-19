#include "game/factory/game_loop_factory.h"

#include <game/game_loop.h>
#include <graphics/factory/renderer_factory.h>
#include <physics/factory/bullet_physics_simulation_factory.h>

namespace ifx {

GameLoopFactory::GameLoopFactory(){}
GameLoopFactory::~GameLoopFactory(){}

std::shared_ptr<GameLoop> GameLoopFactory::Create(
        std::shared_ptr<Renderer> renderer,
        std::shared_ptr<PhysicsSimulation> physics_simulation,
        std::shared_ptr<SceneContainer> scene){
    auto game_loop = std::shared_ptr<GameLoop>(
            new GameLoop(renderer, physics_simulation, scene));
    return game_loop;
}

}