#ifndef PROJECT_SOFT_BODY_VIEW_H
#define PROJECT_SOFT_BODY_VIEW_H

#include <memory>
#include <editor/view.h>

namespace ifx {

class GameUpdater;

class SoftBodyView : public View {
public:
    SoftBodyView(std::unique_ptr<GameUpdater> game_updater);
    ~SoftBodyView() = default;

    virtual void Render() override;
private:
    std::unique_ptr<GameUpdater> game_updater_;
};
}

#endif //PROJECT_SOFT_BODY_VIEW_H
