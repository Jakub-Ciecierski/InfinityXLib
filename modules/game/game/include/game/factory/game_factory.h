#ifndef PROJECT_GAME_FACTORY_H
#define PROJECT_GAME_FACTORY_H

#include <memory>

namespace ifx {

class Game;
class GameLoopFactory;
class SceneContainerFactory;
class RendererFactory;
class PhysicsSimulationFactory;
class ResourceContextFactory;
class RenderingContextFactory;
class WindowFactory;
class ControlsFactory;
class ControlContextFactory;
class GUIContextFactory;
class GUIFactory;
class Window;
class GameLoop;

class GameSystemsFactory;
class GameContextsFactory;

struct EngineContexts;
struct EngineSystems;
struct EngineArchitecture;

class GameFactory {
public:
    GameFactory();
    ~GameFactory() = default;

    GameFactory& SetGameContextsFactory(std::shared_ptr<GameContextsFactory>);
    GameFactory& SetGameSystemsFactory(std::shared_ptr<GameSystemsFactory>);
    GameFactory& SetWindowFactory(std::shared_ptr<WindowFactory>);
    GameFactory& SetGameLoopFactory(std::shared_ptr<GameLoopFactory>);

    std::shared_ptr<Game> Create();

private:
    void CreateDefaultFactories();

    std::shared_ptr<EngineArchitecture> CreateEngineArchitecture();

    void InitContexts(std::shared_ptr<Window> window, EngineContexts &contexts);

    std::shared_ptr<GameContextsFactory> game_contexts_factory_;
    std::shared_ptr<GameSystemsFactory> game_systems_factory_;
    std::shared_ptr<WindowFactory> window_factory_;
    std::shared_ptr<GameLoopFactory> game_loop_factory_;
};
}

#endif //PROJECT_GAME_FACTORY_H
