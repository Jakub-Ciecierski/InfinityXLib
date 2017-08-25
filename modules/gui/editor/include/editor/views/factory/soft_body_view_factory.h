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

struct EngineArchitecture;

class SoftBodyViewFactory : public ViewFactory {
public:
    SoftBodyViewFactory(
            std::shared_ptr<EngineArchitecture> engine_architecture);
    ~SoftBodyViewFactory() = default;

    virtual std::shared_ptr<View> Create() override;
private:
    std::shared_ptr<EngineArchitecture> CreateEngineArchitecture();
    std::unique_ptr<GameSystemsFactory> CreateGameSystemsFactory();

    void SetDefaultScene(std::shared_ptr<SceneContainer> scene,
                         std::shared_ptr<SoftBodyView> soft_body_view);
    void SetRendererSettings(std::shared_ptr<Renderer> renderer,
                             std::shared_ptr<Renderer> old_renderer);

    void SetKeybinds(
            std::shared_ptr<Controls> controls,
            std::shared_ptr<CameraComponent> camera,
            std::shared_ptr<SoftBodyView> soft_body_view);

    std::shared_ptr<EngineArchitecture> engine_architecture_;
};
}

#endif //PROJECT_SOFT_BODY_VIEW_FACTORY_H
