#include "physics/context/factory/bullet_context_factory.h"

#include <physics/context/bullet_physics_context.h>

namespace ifx{

std::shared_ptr<PhysicsContext> BulletContextFactory::Create() {
    return std::make_shared<BulletPhysicsContext>();
}
}
