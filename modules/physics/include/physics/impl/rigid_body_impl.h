#ifndef PROJECT_RIGIDBODYIMPL_H
#define PROJECT_RIGIDBODYIMPL_H

#include <memory>

namespace ifx {

class CollisionShape;

class RigidBodyImpl {
public:

    RigidBodyImpl();

    virtual ~RigidBodyImpl();

    virtual void* GetNativeRigidBody() = 0;

protected:
    virtual void InitImpl(
            std::shared_ptr<CollisionShape> collision_shape,
            float mass) = 0;
private:
};
}


#endif //PROJECT_RIGIDBODYIMPL_H
