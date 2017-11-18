#include "physics/simulations/physx/physx_event_callback.h"

#include <iostream>

namespace ifx {

void PhysXEventCallback::onContact(
    const physx::PxContactPairHeader &pairHeader,
    const physx::PxContactPair *pairs,
    physx::PxU32 nbPairs) {
    std::cout << "PhysX Contact" << std::endl;
}

void PhysXEventCallback::onConstraintBreak(physx::PxConstraintInfo *constraints,
                                           physx::PxU32 count) {

}

void PhysXEventCallback::onWake(physx::PxActor **actors, physx::PxU32 count) {

}

void PhysXEventCallback::onSleep(physx::PxActor **actors, physx::PxU32 count) {

}

void PhysXEventCallback::onTrigger(physx::PxTriggerPair *pairs,
                                   physx::PxU32 count) {

}

void PhysXEventCallback::onAdvance(const physx::PxRigidBody *const *bodyBuffer,
                                   const physx::PxTransform *poseBuffer,
                                   const physx::PxU32 count) {

}

}