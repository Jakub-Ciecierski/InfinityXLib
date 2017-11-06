#ifndef PROJECT_RENDER_OBJECT_MATERIAL_VIEW_H
#define PROJECT_RENDER_OBJECT_MATERIAL_VIEW_H

#include <memory>
#include <vector>

namespace ifx {

class RenderComponent;
class RenderComponent;
struct Material;
class Texture2D;
class ResourceContext;
enum class TextureTypes;

class RenderObjectMaterialView {
public:

    RenderObjectMaterialView(
            std::shared_ptr<ResourceContext> resource_creator);
    ~RenderObjectMaterialView() = default;

    void Render(std::shared_ptr<RenderComponent> render_object);
private:
    void RenderMeshes(std::shared_ptr<RenderComponent> render_object);
    void RenderMaterial(int i, Material& material);

    void RenderAlpha(Material& material);
    void RenderShininess(Material& material);
    void RenderTexture(Material& material,
                       std::shared_ptr<Texture2D> texture,
                       const std::string& name,
                       TextureTypes type);

    void RenderTexturePopup(Material& material, bool open);
    void RenderAssetList(const std::vector<std::string>& textures);
    void RenderFooter(Material& material);
    std::shared_ptr<Texture2D> CreateTexture();

    std::shared_ptr<ResourceContext> resource_creator_;

    int selected_asset_;

    TextureTypes opened_texture_type_;
    std::shared_ptr<Texture2D> opened_texture_;
};
}


#endif //PROJECT_RENDER_OBJECT_MATERIAL_VIEW_H

