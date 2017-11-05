#include "game/factory/game_loop_factory.h"

#include <game/game_loop.h>
#include <game/game_updater.h>

#include <graphics/factory/renderer_factory.h>

#include <physics/factory/bullet_physics_simulation_factory.h>

#include <common/unique_ptr.h>

namespace ifx {

std::shared_ptr<GameLoop> GameLoopFactory::Create(
    std::shared_ptr<EngineArchitecture> engine_architecture) {
    auto game_updater = ifx::make_unique<GameUpdater>(engine_architecture);

    auto game_loop = std::make_shared<GameLoop>(std::move(game_updater));

    return game_loop;
}

}