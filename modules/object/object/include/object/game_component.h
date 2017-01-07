#ifndef PROJECT_GAME_COMPONENT_H
#define PROJECT_GAME_COMPONENT_H

#include <object/movable_object.h>

namespace ifx {

enum class GameComponentType{
    RENDER, PHYSICS, LIGHT, CAMERA
};

/**
 * GameComponent is used to define behavior of a GameObject.
 * It can be anything that the Engine requires (e.g. Renderable, rigid body,
 * light etc.).
 */
class GameComponent : public MovableObject {
public:

    GameComponent(GameComponentType type);
    ~GameComponent();

    GameComponentType type(){return type_;}

    static std::string GetTypeString(GameComponentType type);

private:
    GameComponentType type_;
};
}

#endif //PROJECT_GAME_COMPONENT_H
