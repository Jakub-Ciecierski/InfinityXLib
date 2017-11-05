#ifndef PROJECT_SCENEDISTRIBUTOR_H
#define PROJECT_SCENEDISTRIBUTOR_H

#include <memory>

namespace ifx {

class SceneRenderer;
class RenderComponent;
class LightSource;
class CameraComponent;
class PhysicsSimulation;
class RigidBodyComponent;
class GameObject;
class GameComponent;

template<class T>
class SoftBodyFEMComponent;

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
    void Add(std::shared_ptr<RenderComponent> render_object);
    void Add(std::shared_ptr<LightSource> light_source);
    void Add(std::shared_ptr<CameraComponent> camera);
    void Add(std::shared_ptr<RigidBodyComponent> rigid_body);
    void Add(std::shared_ptr<SoftBodyFEMComponent<double>> soft_body);

    bool Remove(std::shared_ptr<RenderComponent> render_object);
    bool Remove(std::shared_ptr<LightSource> light_source);
    bool Remove(std::shared_ptr<CameraComponent> camera);
    bool Remove(std::shared_ptr<RigidBodyComponent> rigid_body);
    bool Remove(std::shared_ptr<SoftBodyFEMComponent<double>> soft_body);

    std::shared_ptr<SceneRenderer> scene_renderer_;
    std::shared_ptr<PhysicsSimulation> physics_simulation_;
};
}

#endif //PROJECT_SCENEDISTRIBUTOR_H
