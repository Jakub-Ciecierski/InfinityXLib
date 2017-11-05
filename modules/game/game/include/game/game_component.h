#ifndef PROJECT_GAME_COMPONENT_H
#define PROJECT_GAME_COMPONENT_H

#include <string>

#include <controls/controlable.h>

namespace ifx {

enum class GameComponentType {
    RENDER, PHYSICS, LIGHT, CAMERA, PHYSICS_SOFT_BODY
};

/**
 * GameComponent is used to define behavior of a GameObject.
 * It can be anything that the Engine requires (e.g. Renderable, rigid body,
 * light etc.).
 */
class GameComponent : public Controlable {
public:

    GameComponent(GameComponentType type);

    virtual ~GameComponent() = default;

    GameComponentType type() { return type_; }

    static std::string GetTypeString(GameComponentType type);

private:
    GameComponentType type_;
};
}

#endif //PROJECT_GAME_COMPONENT_H
