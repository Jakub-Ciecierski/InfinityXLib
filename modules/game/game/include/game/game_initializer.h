#ifndef PROJECT_GAME_INITIALIZER_H
#define PROJECT_GAME_INITIALIZER_H

namespace ifx {

class Game;

class GameInitializer {
public:
    GameInitializer() = default;
    ~GameInitializer() = default;

    bool Initialize(Game& game);
};
}

#endif //PROJECT_GAME_INITIALIZER_H
