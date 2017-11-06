#ifndef PROJECT_RESOURCE_TEXTURE_VIEW_H
#define PROJECT_RESOURCE_TEXTURE_VIEW_H

namespace ifx {

class ResourceFinder;

class ResourceTextureView {
public:

    ResourceTextureView();
    ~ResourceTextureView() = default;

    void Render(ResourceFinder& resource_finder);
private:
    void RenderGroup(ResourceFinder &resource_finder);
    void RenderList(ResourceFinder &resource_finder);

    void RenderSelectedTexture();

    int selected_;

};
}


#endif //PROJECT_RESOURCE_TEXTURE_VIEW_H
