#ifndef PROJECT_GAME_ARCHITECTURE_H
#define PROJECT_GAME_ARCHITECTURE_H

#include <memory>

namespace ifx {

class RenderingContext;
class ResourceContext;
class ControlContext;
class GUIContext;

class Renderer;
class PhysicsSimulation;
class Controls;
class SceneContainer;
class GUI;

class Window;

struct EngineContexts {
    std::shared_ptr<RenderingContext> rendering_context = nullptr;
    std::shared_ptr<ResourceContext> resource_context = nullptr;
    std::shared_ptr<ControlContext> control_context = nullptr;
    std::shared_ptr<GUIContext> gui_context = nullptr;
};

struct EngineSystems {
    std::shared_ptr<Renderer> renderer = nullptr;
    std::shared_ptr<PhysicsSimulation> physics_simulation = nullptr;
    std::shared_ptr<Controls> controls = nullptr;
    std::shared_ptr<SceneContainer> scene_container = nullptr;
    std::shared_ptr<GUI> gui = nullptr;
};

struct EngineArchitecture {
    std::shared_ptr<Window> window = nullptr;

    EngineContexts engine_contexts;

    EngineSystems engine_systems;
};

}

#endif //PROJECT_GAME_ARCHITECTURE_H
