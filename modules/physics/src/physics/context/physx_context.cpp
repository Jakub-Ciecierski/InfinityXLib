#include "physics/context/physx_context.h"

#include <common/unique_ptr.h>

#define _DEBUG
#include <PxPhysicsAPI.h>

#define PVD_HOST "127.0.0.1"

namespace ifx {

bool PhysxContext::Init() {
    px_allocator_callback_ = ifx::make_unique<physx::PxDefaultAllocator>();
    px_error_callback_ = ifx::make_unique<physx::PxDefaultErrorCallback>();

    px_foundation_
            = PxCreateFoundation(PX_FOUNDATION_VERSION,
                                 *px_allocator_callback_,
                                 *px_error_callback_);
    if(!px_foundation_)
        return false;

    // Visual debugger.
    px_pvd_ = physx::PxCreatePvd(*px_foundation_);
    px_pvd_transport_ = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST,
                                                                 5425, 10);
    px_pvd_->connect(*px_pvd_transport_, physx::PxPvdInstrumentationFlag::eALL);
    px_physics_ = PxCreatePhysics(PX_PHYSICS_VERSION, *px_foundation_,
                                      physx::PxTolerancesScale(),
                                      true, px_pvd_);
    if(!px_physics_)
        return false;

    return true;
}

bool PhysxContext::Terminate() {
    px_physics_->release();
    px_pvd_->release();
    px_pvd_transport_->release();
    px_foundation_->release();

    return true;
}

void* PhysxContext::NativeData(){
    return (void*)px_foundation_;
}

}