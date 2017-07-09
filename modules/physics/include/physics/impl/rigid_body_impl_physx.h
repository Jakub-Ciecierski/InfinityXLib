#ifndef PROJECT_RIGID_BODY_IMPL_PHYSX_H
#define PROJECT_RIGID_BODY_IMPL_PHYSX_H

#include <physics/impl/rigid_body_impl.h>

#include <memory>

namespace physx{
class PxRigidActor;
class PxPhysics;
class PxShape;
class PxMaterial;
}

namespace ifx {

class CollisionShape;

class RigidBodyImplPhysx : public RigidBodyImpl{
public:
    RigidBodyImplPhysx(physx::PxPhysics* px_physics);

    ~RigidBodyImplPhysx();

    void *GetNativeRigidBody() override;

    void InitImpl(std::shared_ptr<CollisionShape> collision_shape,
                  float mass) override;

    void InitCollisionShape(const StaticPlaneShape *shape) override;

    void InitCollisionShape(const BoxCollisionShape *shape) override;

    void SetCollisionShapeScale(const glm::vec3 &scale) override;

    virtual bool IsDynamic() override;
private:
    physx::PxPhysics* px_physics_;

    physx::PxRigidActor* px_rigid_actor_;
    physx::PxShape* px_shape_;
    physx::PxMaterial* px_material_;

    glm::vec3 previous_collision_shape_scale_;
    std::shared_ptr<CollisionShape> ifx_collision_shape_;

    float mass_;
};
}


#endif //PROJECT_RIGID_BODY_IMPL_PHYSX_H
