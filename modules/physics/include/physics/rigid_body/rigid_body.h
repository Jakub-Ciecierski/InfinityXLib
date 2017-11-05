#ifndef PROJECT_RIGID_BODY_TMP_H
#define PROJECT_RIGID_BODY_TMP_H

#include <memory>
#include <math/transform.h>

namespace ifx {

class CollisionShape;
class RigidBodyImpl;

struct RigidBodyParams {
    std::shared_ptr<CollisionShape> collision_shape;
    float mass;
};

class RigidBody : public Transformable {
public:

    RigidBody(std::unique_ptr<RigidBodyImpl> rigid_body_impl,
              const RigidBodyParams &&params);
    ~RigidBody() = default;

    void *GetNativeRigidBody();

    virtual void Update(float time_delta = 0) override;
private:
    std::unique_ptr<RigidBodyImpl> rigid_body_impl_;

    std::shared_ptr<CollisionShape> collision_shape_;
    float mass_;
};
}

#endif //PROJECT_RIGID_BODY_TMP_H
