#ifndef PROJECT_PHYSICS_CONTEXT_H
#define PROJECT_PHYSICS_CONTEXT_H

namespace ifx {

class PhysicsContext {
public:
    PhysicsContext() = default;
    virtual ~PhysicsContext() = default;

    virtual bool Init() = 0;
    virtual bool Terminate() = 0;

    virtual void* NativeData() = 0;
};
}

#endif //PROJECT_PHYSICS_CONTEXT_H
