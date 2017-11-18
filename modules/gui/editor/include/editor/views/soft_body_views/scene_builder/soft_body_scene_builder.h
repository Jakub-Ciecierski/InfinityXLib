#ifndef PROJECT_SCENE_BUILDER_H
#define PROJECT_SCENE_BUILDER_H

#include <memory>

namespace ifx {

class SceneRenderer;
class GameObject;
class PhysicsSimulation;

template<class T>
class SoftBodyFEMComponentBuilder;

class SoftBodySceneBuilder {
public:

    SoftBodySceneBuilder(std::shared_ptr<SceneRenderer> scene_renderer,
                         std::shared_ptr<PhysicsSimulation> physics_simulation_);
    ~SoftBodySceneBuilder() = default;

    void Render(std::shared_ptr<GameObject> game_object,
                SoftBodyFEMComponentBuilder<double>* soft_body_builder);
private:
    void RenderBuild(std::shared_ptr<GameObject> game_object,
                     SoftBodyFEMComponentBuilder<double>* soft_body_builder);
    void RenderInfo();

    std::shared_ptr<SceneRenderer> scene_renderer_;
    std::shared_ptr<PhysicsSimulation> physics_simulation_;
};
}


#endif //PROJECT_SCENE_BUILDER_H
