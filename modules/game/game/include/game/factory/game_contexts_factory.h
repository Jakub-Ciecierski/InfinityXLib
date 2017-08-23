#ifndef PROJECT_GAME_CONTEXTS_FACTORY_H
#define PROJECT_GAME_CONTEXTS_FACTORY_H

#include <game/architecture/engine_architecture.h>

#include <memory>

namespace ifx {

class RenderingContextFactory;
class ResourceContextFactory;
class ControlContextFactory;
class GUIContextFactory;
class PhysicsContextFactory;

class GameContextsFactory {
public:
    GameContextsFactory();
    ~GameContextsFactory() = default;

    GameContextsFactory& SetRenderingContextFactory(
            std::shared_ptr<RenderingContextFactory> factory);
    GameContextsFactory& SetResourceContextFactory(
            std::shared_ptr<ResourceContextFactory> factory);
    GameContextsFactory& SetControlContextFactory(
            std::shared_ptr<ControlContextFactory> factory);
    GameContextsFactory& SetGUIContextFactory(
            std::shared_ptr<GUIContextFactory> factory);
    GameContextsFactory& SetPhysicsContextFactory(
            std::shared_ptr<PhysicsContextFactory> factory);

    EngineContexts Create();

private:
    void CreateDefaultFactories();

    std::shared_ptr<RenderingContextFactory> rendering_context_factory_;
    std::shared_ptr<ResourceContextFactory> resource_context_factory_;
    std::shared_ptr<ControlContextFactory> control_context_factory_;
    std::shared_ptr<GUIContextFactory> gui_context_factory_;
    std::shared_ptr<PhysicsContextFactory> physics_context_factory_;
};
}

#endif //PROJECT_GAME_CONTEXTS_FACTORY_H
