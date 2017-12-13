#ifndef PROJECT_RIGID_BODY_IMPL_PHYSX_H
#define PROJECT_RIGID_BODY_IMPL_PHYSX_H

#include <physics/rigid_body/impl/rigid_body_impl.h>

#include <memory>

namespace physx {
class PxRigidActor;
class PxPhysics;
class PxShape;
class PxMaterial;
}

namespace ifx {

class CollisionShape;

class RigidBodyImplPhysx : public RigidBodyImpl {
public:
    RigidBodyImplPhysx(physx::PxPhysics *px_physics);

    ~RigidBodyImplPhysx();

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

    virtual void SetVelocity(const glm::vec3& velocity) override;
    virtual glm::vec3 GetVelocity() override;
private:
    physx::PxPhysics *px_physics_;

    physx::PxRigidActor *px_rigid_actor_;
    physx::PxShape *px_shape_;
    physx::PxMaterial *px_material_;

};
}

#endif //PROJECT_RIGID_BODY_IMPL_PHYSX_H