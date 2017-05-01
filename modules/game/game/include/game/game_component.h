#ifndef PROJECT_GAME_COMPONENT_H
#define PROJECT_GAME_COMPONENT_H

#include <string>

namespace ifx {

enum class GameComponentType{
    RENDER, PHYSICS, LIGHT, CAMERA
};

/**
 * GameComponent is used to define behavior of a GameObject.
 * It can be anything that the Engine requires (e.g. Renderable, rigid body,
 * light etc.).
 */
class GameComponent {
public:

    GameComponent(GameComponentType type);

    virtual ~GameComponent();

    GameComponentType type(){return type_;}

    static std::string GetTypeString(GameComponentType type);

private:
    GameComponentType type_;
};
}

#endif //PROJECT_GAME_COMPONENT_H
