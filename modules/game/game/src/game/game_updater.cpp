#include "game/game_updater.h"

#include <graphics/rendering/renderer.h>
#include <graphics/rendering/window/window.h>

#include <physics/physics_simulation.h>

#include <game/scene_container.h>
#include <game/architecture/engine_architecture.h>

#include <controls/controls.h>

#include <gui/gui.h>

namespace ifx {

GameUpdater::GameUpdater(
    std::shared_ptr<EngineArchitecture> engine_architecture) :
    engine_architecture_(engine_architecture) {}

void GameUpdater::Update(float time_elapsed) {
    auto &systems = engine_architecture_->engine_systems;

    if (systems.physics_simulation)
        systems.physics_simulation->Update(time_elapsed);
    if (systems.scene_container)
        systems.scene_container->Update();
    if (systems.controls)
        systems.controls->Update();
    if (systems.renderer)
        systems.renderer->Update();
    if (systems.gui)
        systems.gui->Update();

    if (engine_architecture_->window)
        engine_architecture_->window->Update();
}

}
