#ifndef PROJECT_BULLET_PHYSICS_CONTEXT_H
#define PROJECT_BULLET_PHYSICS_CONTEXT_H

#include "physics/context/physics_context.h"

namespace ifx {

class BulletPhysicsContext : public PhysicsContext {
public:
    BulletPhysicsContext() = default;
    ~BulletPhysicsContext() = default;

    virtual bool Init() override;

    virtual bool Terminate() override;

    virtual void *NativeData() override;
};

}

#endif //PROJECT_BULLET_PHYSICS_CONTEXT_H
