#ifndef PROJECT_GAME_OBJECT_H
#define PROJECT_GAME_OBJECT_H

#include <memory>

#include <object/movable_object.h>

namespace ifx {

class GameComponent;
class SceneDistributor;
enum class GameComponentType;

/**
 * GameObject is used to encapsulate an object in the game scene.
 * It can contained multiply GameComponents of different types (e.g. rigid
 * body, renderable, lights etc.).
 *
 * Other class should be responsible of dividing all GameObjects into
 * specific components and sending them to further process (e.g. all
 * render_objects should be be sent to the renderer.)
 */
class GameObject : public MovableObject {
public:
    GameObject(std::shared_ptr<SceneDistributor> scene_distributor);

    ~GameObject();

    // Overridden from MovableObject
    virtual void update() override;

    void Add(std::shared_ptr<GameComponent> game_component);
    bool Remove(std::shared_ptr<GameComponent> game_component);

    std::vector<std::shared_ptr<GameComponent>> GetComponents(
            const GameComponentType&& type);
    std::vector<std::shared_ptr<GameComponent>>& GetComponents();

    bool Exists(std::shared_ptr<GameComponent> game_component);
private:
    std::vector<std::shared_ptr<GameComponent>> components_;

    std::shared_ptr<SceneDistributor> scene_distributor_;

};
}

#endif //PROJECT_GAME_OBJECT_H
