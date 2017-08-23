#include "physics/context/factory/physx_context_factory.h"

#include "physics/context/physics_context.h"
#include <physics/context/physx_context.h>

#define _DEBUG
#include <PxPhysicsAPI.h>

namespace ifx{

std::shared_ptr<PhysicsContext> PhysxContextFactory::Create() {
    return std::make_shared<PhysxContext>();
}

}
