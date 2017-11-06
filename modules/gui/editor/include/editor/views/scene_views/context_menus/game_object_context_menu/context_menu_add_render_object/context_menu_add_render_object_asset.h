#ifndef PROJECT_CONTEXT_MENU_ADD_RENDER_OBJECT_ASSET_H
#define PROJECT_CONTEXT_MENU_ADD_RENDER_OBJECT_ASSET_H

#include <memory>
#include <vector>

namespace ifx {

class SceneRenderer;
class ResourceContext;
class GameObject;
class RenderComponent;

class ContextMenuAddRenderObjectAsset {
public:
    ContextMenuAddRenderObjectAsset();
    ~ContextMenuAddRenderObjectAsset() = default;

    void Render(
            std::shared_ptr<SceneRenderer> scene_renderer,
            std::shared_ptr<ResourceContext> resource_creator,
            std::shared_ptr<GameObject> game_object);
private:
    void RenderAssetList(const std::vector<std::string>& models);
    void RenderFooter(std::shared_ptr<SceneRenderer> scene_renderer,
                      std::shared_ptr<ResourceContext> resource_creator,
                      std::shared_ptr<GameObject> game_object);
    std::shared_ptr<RenderComponent> CreateRenderComponent(
            std::shared_ptr<SceneRenderer> scene_renderer,
            std::shared_ptr<ResourceContext> resource_creator);

    int selected_asset_;

};

}

#endif //PROJECT_CONTEXT_MENU_ADD_RENDER_OBJECT_ASSET_H
