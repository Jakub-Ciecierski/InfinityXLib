#ifndef PROJECT_RENDER_OBJECT_VIEW_H
#define PROJECT_RENDER_OBJECT_VIEW_H

#include <memory>

namespace ifx {

class RenderComponent;

class RenderObjectView {
public:

    RenderObjectView();
    ~RenderObjectView();

    void Render(std::shared_ptr<RenderComponent> render_object);
private:
};
}

#endif //PROJECT_RENDER_OBJECT_VIEW_H
