#ifndef PROJECT_PHYSX_COLLISION_CALLBACK_H
#define PROJECT_PHYSX_COLLISION_CALLBACK_H

#define _DEBUG
#include <PxSimulationEventCallback.h>

namespace ifx {

class PhysXEventCallback : public physx::PxSimulationEventCallback {
public:
    PhysXEventCallback() = default;
    ~PhysXEventCallback() = default;

    virtual void onContact(const physx::PxContactPairHeader &pairHeader,
                           const physx::PxContactPair *pairs,
                           physx::PxU32 nbPairs) override;
    virtual void onConstraintBreak(physx::PxConstraintInfo *constraints,
                                   physx::PxU32 count) override;
    virtual void onWake(physx::PxActor **actors, physx::PxU32 count) override;
    virtual void onSleep(physx::PxActor **actors, physx::PxU32 count) override;
    virtual void onTrigger(physx::PxTriggerPair *pairs,
                           physx::PxU32 count) override;
    virtual void onAdvance(const physx::PxRigidBody *const *bodyBuffer,
                           const physx::PxTransform *poseBuffer,
                           const physx::PxU32 count) override;
private:
};

}

#endif //PROJECT_PHYSX_COLLISION_CALLBACK_H
