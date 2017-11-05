#ifndef PROJECT_SOFT_BODY_VIEW_FACTORY_H
#define PROJECT_SOFT_BODY_VIEW_FACTORY_H

#include <memory>

#include "editor/views/factory/view_factory.h"

namespace ifx {

class SoftBodyView;
class GameSystemsFactory;
class SceneContainer;
class Renderer;
class Controls;
class CameraComponent;
class GameLoop;

struct EngineArchitecture;
struct SoftBodyRenderingEffects;

extern const std::string NODE_RENDERING_EFFECT_NAME;
extern const std::string EDGES_RENDERING_EFFECT_NAME;
extern const std::string FACES_RENDERING_EFFECT_NAME;

class SoftBodyViewFactory : public ViewFactory {
public:
    SoftBodyViewFactory(
        std::shared_ptr<GameLoop> game_loop,
        std::shared_ptr<EngineArchitecture> engine_architecture);
    ~SoftBodyViewFactory() = default;

    virtual std::shared_ptr<View> Create() override;
private:
    std::shared_ptr<EngineArchitecture> CreateEngineArchitecture();
    std::unique_ptr<GameSystemsFactory> CreateGameSystemsFactory();

    SoftBodyRenderingEffects SetRendererSettings(
        std::shared_ptr<Renderer> renderer,
        std::shared_ptr<Renderer> old_renderer);
    SoftBodyRenderingEffects CreateRenderingEffects(
        std::shared_ptr<Renderer> old_renderer);

    void SetDefaultScene(std::shared_ptr<SceneContainer> scene,
                         std::shared_ptr<SoftBodyView> soft_body_view);

    void SetKeybinds(
        std::shared_ptr<Controls> controls,
        std::shared_ptr<CameraComponent> camera,
        std::shared_ptr<SoftBodyView> soft_body_view);

    std::shared_ptr<GameLoop> game_loop_;
    std::shared_ptr<EngineArchitecture> engine_architecture_;
};
}

#endif //PROJECT_SOFT_BODY_VIEW_FACTORY_H
