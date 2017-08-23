#ifndef PROJECT_PHYSICS_CONTEXT_FACTORY_H
#define PROJECT_PHYSICS_CONTEXT_FACTORY_H

#include <memory>

namespace ifx {

class PhysicsContext;

class PhysicsContextFactory {
public:
    PhysicsContextFactory() = default;
    virtual ~PhysicsContextFactory() = default;

    virtual std::shared_ptr<PhysicsContext> Create() = 0;
};
}

#endif //PROJECT_PHYSICS_CONTEXT_FACTORY_H
