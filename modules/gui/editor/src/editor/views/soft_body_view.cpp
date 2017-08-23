#include "editor/views/soft_body_view.h"

#include <game/game_updater.h>
#include <game/architecture/engine_architecture.h>

#include <physics/physics_simulation.h>

namespace ifx{

SoftBodyView::SoftBodyView(std::unique_ptr<GameUpdater> game_updater) :
        View("Soft Body"),
        game_updater_(std::move(game_updater)){}

bool SoftBodyView::Terminate() {
    game_updater_->engine_architecture()->engine_systems
            .physics_simulation->Terminate();
    return true;
}

void SoftBodyView::Render(){
    game_updater_->Update(1.0f/60.0f);
}

}
