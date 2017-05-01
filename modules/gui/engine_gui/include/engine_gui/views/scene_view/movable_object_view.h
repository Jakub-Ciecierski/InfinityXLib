#ifndef PROJECT_MOVABLE_OBJECT_VIEW_H
#define PROJECT_MOVABLE_OBJECT_VIEW_H

#include <memory>

namespace ifx {

class Transformable;

class MovableObjectView {
public:

    MovableObjectView();
    ~MovableObjectView();

    void Render(std::shared_ptr<Transformable> movable_object);
private:

    void RenderPosition(std::shared_ptr<Transformable> movable_object);
    void RenderRotation(std::shared_ptr<Transformable> movable_object);
    void RenderScale(std::shared_ptr<Transformable> movable_object);
    void RenderDirection(std::shared_ptr<Transformable> movable_object);

};
}

#endif //PROJECT_MOVABLE_OBJECT_VIEW_H
