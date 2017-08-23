#ifndef PROJECT_PHYSX_PHYSICS_SIMULATION_H
#define PROJECT_PHYSX_PHYSICS_SIMULATION_H

#include <physics/physics_simulation.h>

namespace physx{
class PxPhysics;

class PxPvd;
class PxPvdTransport;

class PxFoundation;
class PxAllocatorCallback;
class PxErrorCallback;

class PxDefaultCpuDispatcher;
class PxScene;
}

namespace ifx {

class PhysxPhysicsSimulation : public PhysicsSimulation {
public:
    PhysxPhysicsSimulation(
            std::shared_ptr<PhysicsContext> physics_context,
            physx::PxPhysics *px_physics,
            physx::PxPvd *px_pvd,
            physx::PxPvdTransport *px_pvd_transport,
            physx::PxDefaultCpuDispatcher *px_dispatcher,
            physx::PxScene *px_scene
    );

    ~PhysxPhysicsSimulation() = default;

    virtual bool Terminate() override;

    virtual void Update(float time_delta) override;

    virtual void Add(std::shared_ptr<RigidBody> rigid_body) override;
    virtual bool Remove(std::shared_ptr<RigidBody> rigid_body) override;

    virtual void SetGravity(const glm::vec3 &g) override;
    virtual glm::vec3 GetGravity() override;

    virtual void AddImpulse() override;

    virtual std::unique_ptr<RigidBodyImpl> CreateRigidBodyImpl() override;

    void SynchronizeRigidBodiesTransform();
    void SynchronizeGameObjectsTransform();
private:
    physx::PxPhysics* px_physics_;
    physx::PxPvd* px_pvd_;
    physx::PxPvdTransport* px_pvd_transport_;

    physx::PxDefaultCpuDispatcher* px_dispatcher_;
    physx::PxScene* px_scene_;
};
}


#endif //PROJECT_PHYSX_PHYSICS_SIMULATION_H
