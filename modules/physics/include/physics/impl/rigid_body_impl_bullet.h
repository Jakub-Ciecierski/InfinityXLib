#ifndef PROJECT_RIGID_BODY_IMPL_BULLET_H
#define PROJECT_RIGID_BODY_IMPL_BULLET_H

#include <physics/impl/rigid_body_impl.h>

#include <memory>

class btRigidBody;
class btCollisionShape;

namespace ifx {

class CollisionShape;
class BoxCollisionShape;
class StaticPlaneShape;

class RigidBodyImplBullet : public RigidBodyImpl {
public:

    RigidBodyImplBullet();

    ~RigidBodyImplBullet();

    virtual void* GetNativeRigidBody() override;

    virtual void InitImpl(std::shared_ptr<CollisionShape> collision_shape,
                          float mass) override;

    virtual void InitCollisionShape(const StaticPlaneShape* shape) override;
    virtual void InitCollisionShape(const BoxCollisionShape* shape) override;

    virtual void SetCollisionShapeScale(const glm::vec3& scale) override;

    virtual bool IsDynamic() override;

private:
    std::shared_ptr<btCollisionShape> collision_shape_bt_;
    std::unique_ptr<btRigidBody> rigid_body_bt_;

    std::shared_ptr<CollisionShape> ifx_collision_shape_;

};
}


#endif //PROJECT_RIGID_BODY_IMPL_BULLET_H
