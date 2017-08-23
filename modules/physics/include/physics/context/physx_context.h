#ifndef PROJECT_PHYSX_CONTEXT_H
#define PROJECT_PHYSX_CONTEXT_H

#include "physics/context/physics_context.h"

#include <memory>

namespace physx {

class PxFoundation;
class PxAllocatorCallback;
class PxErrorCallback;

}

namespace ifx {

class PhysxContext : public PhysicsContext {
public:
    PhysxContext() = default;
    ~PhysxContext() = default;

    virtual bool Init() override;

    virtual bool Terminate() override;

    virtual void* NativeData() override;

private:

    physx::PxFoundation* px_foundation_;
    std::unique_ptr<physx::PxAllocatorCallback> px_allocator_callback_;
    std::unique_ptr<physx::PxErrorCallback> px_error_callback_;
};
}

#endif //PROJECT_PHYSX_CONTEXT_H
