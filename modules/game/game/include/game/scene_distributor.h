#ifndef PROJECT_SCENEDISTRIBUTOR_H
#define PROJECT_SCENEDISTRIBUTOR_H

#include <memory>

namespace ifx {

class SceneRenderer;
class RenderObject;
class LightSource;
class Camera;
class PhysicsSimulation;
class RigidBody;
class GameObject;
class GameComponent;

/**
 * Distributes Game Components around to sub systems (e.g. render objects to
 * scene renderer.).
 */
class SceneDistributor {
public:
    SceneDistributor(std::shared_ptr<SceneRenderer> scene_renderer,
                     std::shared_ptr<PhysicsSimulation> physics_simulation);
    ~SceneDistributor();

    void Add(std::shared_ptr<GameObject> game_object);
    bool Remove(std::shared_ptr<GameObject> game_object);

    void Add(std::shared_ptr<GameComponent> game_component);
    bool Remove(std::shared_ptr<GameComponent> game_component);

private:
    void Add(std::shared_ptr<RenderObject> render_object);
    void Add(std::shared_ptr<LightSource> light_source);
    void Add(std::shared_ptr<Camera> camera);
    void Add(std::shared_ptr<RigidBody> rigid_body);

    bool Remove(std::shared_ptr<RenderObject> render_object);
    bool Remove(std::shared_ptr<LightSource> light_source);
    bool Remove(std::shared_ptr<Camera> camera);
    bool Remove(std::shared_ptr<RigidBody> rigid_body);


    std::shared_ptr<SceneRenderer> scene_renderer_;
    std::shared_ptr<PhysicsSimulation> physics_simulation_;
};
}

#endif //PROJECT_SCENEDISTRIBUTOR_H
