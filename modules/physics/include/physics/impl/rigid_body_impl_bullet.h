#ifndef PROJECT_RIGID_BODY_IMPL_BULLET_H
#define PROJECT_RIGID_BODY_IMPL_BULLET_H

#include <physics/impl/rigid_body_impl.h>

#include <memory>

class btRigidBody;

namespace ifx {

class RigidBodyImplBullet : public RigidBodyImpl{
public:

    RigidBodyImplBullet();

    ~RigidBodyImplBullet();

    virtual void* GetNativeRigidBody() override;

protected:
    virtual void InitImpl(std::shared_ptr<CollisionShape> collision_shape,
                          float mass) override;
private:
    std::unique_ptr<btRigidBody> rigid_body_bt_;

};
}


#endif //PROJECT_RIGID_BODY_IMPL_BULLET_H
