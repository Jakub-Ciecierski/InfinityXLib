#ifndef PROJECT_RIGID_BODY_VIEW_H
#define PROJECT_RIGID_BODY_VIEW_H

#include <memory>

namespace ifx {

class RigidBody;

class RigidBodyView {
public:

    RigidBodyView();
    ~RigidBodyView();

    void Render(std::shared_ptr<RigidBody> rigid_body);
private:
    void RenderLinearVelocity(std::shared_ptr<RigidBody> rigid_body);
};
}

#endif //PROJECT_RIGID_BODY_VIEW_H
