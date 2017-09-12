#ifndef PROJECT_BULLTET_CONTEXT_FACTORY_H
#define PROJECT_BULLTET_CONTEXT_FACTORY_H

#include "physics_context_factory.h"

namespace ifx {

class BulletContextFactory : public PhysicsContextFactory {
public:
    BulletContextFactory() = default;

    ~BulletContextFactory() = default;

    std::shared_ptr<PhysicsContext> Create() override;
};

}

#endif //PROJECT_BULLTET_CONTEXT_FACTORY_H
