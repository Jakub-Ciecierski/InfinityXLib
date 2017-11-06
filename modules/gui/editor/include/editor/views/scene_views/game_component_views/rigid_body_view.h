#ifndef PROJECT_RIGID_BODY_VIEW_H
#define PROJECT_RIGID_BODY_VIEW_H

#include <memory>

namespace ifx {

class RigidBodyComponent;

class RigidBodyView {
public:

    RigidBodyView() = default;
    ~RigidBodyView() = default;

    void Render(std::shared_ptr<RigidBodyComponent> rigd_body_component);

private:
};
}


#endif //PROJECT_RIGID_BODY_VIEW_H
