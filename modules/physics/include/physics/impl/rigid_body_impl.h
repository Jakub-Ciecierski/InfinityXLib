#ifndef PROJECT_RIGIDBODYIMPL_H
#define PROJECT_RIGIDBODYIMPL_H

#include <memory>
#include <math/math_ifx.h>

namespace ifx {

class CollisionShape;
class StaticPlaneShape;
class BoxCollisionShape;

class RigidBodyImpl {
public:

    RigidBodyImpl();

    virtual ~RigidBodyImpl();

    virtual void* GetNativeRigidBody() = 0;

    virtual void InitImpl(
            std::shared_ptr<CollisionShape> collision_shape,
            float mass) = 0;
    virtual void InitCollisionShape(const StaticPlaneShape* shape) = 0;
    virtual void InitCollisionShape(const BoxCollisionShape* shape) = 0;

    virtual void SetCollisionShapeScale(const glm::vec3& scale) = 0;

private:
};
}


#endif //PROJECT_RIGIDBODYIMPL_H
