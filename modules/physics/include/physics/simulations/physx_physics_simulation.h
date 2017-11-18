#ifndef PROJECT_PHYSX_PHYSICS_SIMULATION_H
#define PROJECT_PHYSX_PHYSICS_SIMULATION_H

#include <physics/physics_simulation.h>

namespace physx {
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

class PhysXEventCallback;

class PhysxPhysicsSimulation : public PhysicsSimulation {
public:
    PhysxPhysicsSimulation(
        std::shared_ptr<PhysicsContext> physics_context,
        physx::PxDefaultCpuDispatcher *px_dispatcher,
        physx::PxScene *px_scene,
        std::unique_ptr<PhysXEventCallback> event_callback
    );

    ~PhysxPhysicsSimulation() = default;

    virtual bool Terminate() override;

    virtual void Add(std::shared_ptr<RigidBody> rigid_body) override;
    virtual bool Remove(std::shared_ptr<RigidBody> rigid_body) override;

    virtual void SetGravity(const glm::vec3 &g) override;
    virtual glm::vec3 GetGravity() override;

    virtual void AddImpulse() override;

    virtual std::unique_ptr<RigidBodyImpl> CreateRigidBodyImpl() override;

    void SynchronizeRigidBodiesTransform();
    void SynchronizeGameObjectsTransform();
protected:
    virtual void UpdateFixedContent() override;

private:
    physx::PxDefaultCpuDispatcher *px_dispatcher_;
    physx::PxScene *px_scene_;

    std::unique_ptr<PhysXEventCallback> event_callback_;
};
}

#endif //PROJECT_PHYSX_PHYSICS_SIMULATION_H
