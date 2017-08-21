#ifndef PROJECT_GAME_UPDATER_H
#define PROJECT_GAME_UPDATER_H

#include <memory>

namespace ifx {

struct EngineArchitecture;

class GameUpdater {
public:
    GameUpdater(std::shared_ptr<EngineArchitecture> engine_architecture);
    ~GameUpdater() = default;

    void Update(float time_elapsed);

private:
    std::shared_ptr<EngineArchitecture> engine_architecture_;
};
}

#endif //PROJECT_GAME_UPDATER_H
