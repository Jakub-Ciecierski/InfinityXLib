#ifndef PROJECT_RESOURCE_MODEL_VIEW_H
#define PROJECT_RESOURCE_MODEL_VIEW_H

namespace ifx {

class ResourceFinder;

class ResourceModelView {
public:

    ResourceModelView();
    ~ResourceModelView() = default;

    void Render(ResourceFinder& resource_finder);
private:
    void RenderGroup(ResourceFinder &resource_finder);
    void RenderList(ResourceFinder &resource_finder);

    int selected_;
};
}


#endif //PROJECT_RESOURCE_MODEL_VIEW_H
