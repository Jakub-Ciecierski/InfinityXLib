#ifndef PROJECT_SCENE_CONTAINER_H
#define PROJECT_SCENE_CONTAINER_H

#include <memory>
#include <vector>

namespace ifx {

class GameObject;
class SceneRenderer;
class SceneDistributor;
class PhysicsSimulation;
class Camera;

/**
 * Container for GameObjects. Distributes game components to sub systems.
 */
class  SceneContainer {
public:

    SceneContainer(std::shared_ptr<SceneRenderer> scene_renderer,
                   std::shared_ptr<PhysicsSimulation> physics_simulation);
    ~SceneContainer();

    std::vector<std::shared_ptr<GameObject>>& game_objects(){
        return game_objects_;}

    void Update();

    void Add(std::shared_ptr<GameObject> game_object);
    bool Remove(std::shared_ptr<GameObject> game_object);

    std::shared_ptr<Camera> GetActiveCamera();

private:
    void OnAdd(std::shared_ptr<GameObject> game_object);
    bool OnRemove(std::shared_ptr<GameObject> game_object);

    std::vector<std::shared_ptr<GameObject>> game_objects_;

    std::shared_ptr<SceneDistributor> scene_distributor_;

};
}

#endif //PROJECT_SCENE_CONTAINER_H