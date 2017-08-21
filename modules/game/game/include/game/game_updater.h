#ifndef PROJECT_GAME_UPDATER_H
#define PROJECT_GAME_UPDATER_H

#include <memory>

#include <common/updatable.h>

namespace ifx {

struct EngineArchitecture;

class GameUpdater : public Updatable{
public:
    GameUpdater(std::shared_ptr<EngineArchitecture> engine_architecture);
    ~GameUpdater() = default;

    virtual void Update(float time_elapsed) override;

private:
    std::shared_ptr<EngineArchitecture> engine_architecture_;
};
}

#endif //PROJECT_GAME_UPDATER_H
