#ifndef PROJECT_PHYSX_CONTEXT_FACTORY_H
#define PROJECT_PHYSX_CONTEXT_FACTORY_H

#include "physics_context_factory.h"

namespace ifx {

class PhysxContextFactory : public PhysicsContextFactory {
public:
    PhysxContextFactory() = default;
    ~PhysxContextFactory() = default;

    std::shared_ptr<PhysicsContext> Create() override;
};
}

#endif //PROJECT_PHYSX_CONTEXT_FACTORY_H
