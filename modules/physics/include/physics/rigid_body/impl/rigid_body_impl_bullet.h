#ifndef PROJECT_RIGID_BODY_IMPL_BULLET_H
#define PROJECT_RIGID_BODY_IMPL_BULLET_H

#include <physics/rigid_body/impl/rigid_body_impl.h>

#include <memory>

class btRigidBody;
class btCollisionShape;

namespace ifx {

class CollisionShape;
class BoxCollisionShape;
class StaticPlaneShape;

class RigidBodyImplBullet : public RigidBodyImpl {
public:

    RigidBodyImplBullet() = default;
    ~RigidBodyImplBullet() = default;

    virtual void *GetNativeRigidBody() override;

    virtual void InitImpl(std::shared_ptr<CollisionShape> collision_shape,
                          float mass,
                          const PhysicsMaterial& physics_material) override;

    virtual void InitCollisionShape(const StaticPlaneShape *shape) override;
    virtual void InitCollisionShape(const BoxCollisionShape *shape) override;
    virtual void InitCollisionShape(const SphereCollisionShape *shape) override;
    virtual void InitCollisionShape(const MeshCollisionShape *shape) override;

    virtual void SetCollisionShapeScale(const glm::vec3 &scale) override;

    virtual bool IsDynamic() override;

    virtual void SetMass(float mass) override;
    virtual void SetPhysicsMaterial(const PhysicsMaterial& physics_material) override;

    virtual void SetIsKinematic(bool is_kinematic) override;

    virtual void SetUserData(void* user_data_) override;

    virtual void SetGlobalTransform(const glm::vec3 &position,
                                    const glm::quat &rotation) override;
private:
    std::shared_ptr<btCollisionShape> collision_shape_bt_;
    std::unique_ptr<btRigidBody> rigid_body_bt_;

    std::shared_ptr<CollisionShape> ifx_collision_shape_;

};
}

#endif //PROJECT_RIGID_BODY_IMPL_BULLET_H
