#include "physics/context/physx_context.h"

#include <common/unique_ptr.h>

#define _DEBUG
#include <PxPhysicsAPI.h>

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

    return true;
}

bool PhysxContext::Terminate() {
    px_foundation_->release();

    return true;
}

void* PhysxContext::NativeData(){
    return (void*)px_foundation_;
}

}