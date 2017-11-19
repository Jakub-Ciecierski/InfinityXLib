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
    void RenderVelocity(RigidBodyComponent& rigd_body_component);
    void RenderCollisionShape(RigidBodyComponent& rigd_body_component);
    void RenderMass(RigidBodyComponent& rigd_body_component);
    void RenderPhysicsMaterial(RigidBodyComponent& rigd_body_component);
    void RenderIsKinematic(RigidBodyComponent& rigid_body_component);


};
}


#endif //PROJECT_RIGID_BODY_VIEW_H
