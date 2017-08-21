#include "game/game_updater.h"

#include <graphics/rendering/renderer.h>

#include <physics/physics_simulation.h>

#include <game/scene_container.h>
#include <game/architecture/engine_architecture.h>

#include <controls/controls.h>

#include <gui/gui.h>

namespace ifx{
GameUpdater::GameUpdater(
        std::shared_ptr<EngineArchitecture> engine_architecture) :
        engine_architecture_(engine_architecture){}

void GameUpdater::Update(float time_elapsed){
    engine_architecture_->engine_systems.physics_simulation->Update(
            time_elapsed);
    engine_architecture_->engine_systems.scene_container->Update();
    engine_architecture_->engine_systems.controls->Update();

    engine_architecture_->engine_systems.renderer->Update();
    engine_architecture_->engine_systems.gui->Update();

    engine_architecture_->window->Update();
}

}
