#ifndef PROJECT_SCENE_FACTORY_H
#define PROJECT_SCENE_FACTORY_H

#include <memory>

namespace ifx {

class SceneContainer;
class SceneRenderer;
class PhysicsSimulation;

class SceneContainerFactory {
public:

    SceneContainerFactory();
    ~SceneContainerFactory();

    std::shared_ptr<SceneContainer> Create(
            std::shared_ptr<SceneRenderer> scene_renderer,
            std::shared_ptr<PhysicsSimulation> physics_simulation);
private:

};
}

#endif //PROJECT_SCENE_FACTORY_H
