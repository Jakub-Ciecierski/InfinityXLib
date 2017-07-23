#ifndef PROJECT_GAME_COMPONENT_CONTEXT_MENU_H
#define PROJECT_GAME_COMPONENT_CONTEXT_MENU_H

#include <memory>

namespace ifx {

class GameObject;
class GameComponent;

class GameComponentContextMenu {
public:
    GameComponentContextMenu();
    ~GameComponentContextMenu();

    void Render(std::shared_ptr <GameObject> game_object,
                std::shared_ptr <GameComponent> component,
                int component_id);
private:
    void Remove(std::shared_ptr<GameObject> game_object,
                std::shared_ptr<GameComponent> component);
};

}

#endif //PROJECT_GAME_COMPONENT_CONTEXT_MENU_H