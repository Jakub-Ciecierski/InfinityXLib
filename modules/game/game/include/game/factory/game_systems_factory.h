#ifndef PROJECT_GAME_SYSTEMS_FACTORY_H
#define PROJECT_GAME_SYSTEMS_FACTORY_H

#include <game/architecture/engine_architecture.h>

namespace ifx {

class RendererFactory;
class PhysicsSimulationFactory;
class ControlsFactory;
class SceneContainerFactory;
class GUIFactory;

class GameSystemsFactory {
public:
    GameSystemsFactory();
    ~GameSystemsFactory() = default;

    GameSystemsFactory &SetRendererFactory(
        std::shared_ptr<RendererFactory> renderer_factory);
    GameSystemsFactory &SetPhysicsSimulationFactory(
        std::shared_ptr<PhysicsSimulationFactory>
        physics_simulation_factory);
    GameSystemsFactory &SetControlsFactory(
        std::shared_ptr<ControlsFactory> factory);
    GameSystemsFactory &SetSceneContainerFactory(
        std::shared_ptr<SceneContainerFactory> scene_factory);
    GameSystemsFactory &SetGUIFactory(
        std::shared_ptr<GUIFactory> factory);

    EngineSystems Create(std::shared_ptr<Window> window,
                         const EngineContexts &engine_contexts);
private:
    void CreateDefaultFactories();

    std::shared_ptr<RendererFactory> renderer_factory_;
    std::shared_ptr<PhysicsSimulationFactory> physics_simulation_factory_;
    std::shared_ptr<ControlsFactory> controls_factory_;
    std::shared_ptr<SceneContainerFactory> scene_factory_;
    std::shared_ptr<GUIFactory> gui_factory_;
};
}

#endif //PROJECT_GAME_SYSTEMS_FACTORY_H
