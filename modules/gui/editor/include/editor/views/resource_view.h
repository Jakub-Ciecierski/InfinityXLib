#ifndef PROJECT_RESOURCE_VIEW_H
#define PROJECT_RESOURCE_VIEW_H

#include <editor/view.h>

#include <memory>

namespace ifx {

class ResourceContext;
class ResourceModelView;
class ResourceTextureView;

class ResourceView : public View {
public:

    ResourceView(std::shared_ptr<ResourceContext> resource_context_);
    ~ResourceView() = default;

    virtual void Render() override;
private:
    void RenderUpdate();
    void RenderTextures();
    void RenderModels();

    std::shared_ptr<ResourceContext> resource_context_;

    std::unique_ptr<ResourceModelView> model_view_;
    std::unique_ptr<ResourceTextureView> texture_view_;
};
}


#endif //PROJECT_RESOURCE_VIEW_H
