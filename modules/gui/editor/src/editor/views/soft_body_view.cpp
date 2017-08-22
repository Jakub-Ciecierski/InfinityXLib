#include "editor/views/soft_body_view.h"

#include <game/game_updater.h>

namespace ifx{

SoftBodyView::SoftBodyView(std::unique_ptr<GameUpdater> game_updater) :
        View("Soft Body"),
        game_updater_(std::move(game_updater)){}

void SoftBodyView::Render(){
    game_updater_->Update(1.0f/60.0f);
}

}
