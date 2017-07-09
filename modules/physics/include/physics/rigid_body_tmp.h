#ifndef PROJECT_RIGID_BODY_TMP_H
#define PROJECT_RIGID_BODY_TMP_H

#include <memory>
#include <math/transform.h>

namespace ifx {

class CollisionShape;
class RigidBodyImpl;

struct RigidBodyParams{
    std::shared_ptr<CollisionShape> collision_shape;
    float mass;
};

class RigidBodyTMP : public Transformable{
public:

    RigidBodyTMP(std::unique_ptr<RigidBodyImpl> rigid_body_impl,
                 const RigidBodyParams&& params);
    ~RigidBodyTMP();

    void* GetNativeRigidBody();

private:
    std::unique_ptr<RigidBodyImpl> rigid_body_impl_;

    std::shared_ptr<CollisionShape> collision_shape_;
    float mass_;
};
}


#endif //PROJECT_RIGID_BODY_TMP_H
