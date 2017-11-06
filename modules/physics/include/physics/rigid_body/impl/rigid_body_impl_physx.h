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

    virtual void SetCollisionShapeScale(const glm::vec3 &scale) override;

    virtual bool IsDynamic() override;
private:
    physx::PxPhysics *px_physics_;

    physx::PxRigidActor *px_rigid_actor_;
    physx::PxShape *px_shape_;
    physx::PxMaterial *px_material_;

    glm::vec3 previous_collision_shape_scale_;
    std::shared_ptr<CollisionShape> ifx_collision_shape_;

    float mass_;
};
}

#endif //PROJECT_RIGID_BODY_IMPL_PHYSX_H
