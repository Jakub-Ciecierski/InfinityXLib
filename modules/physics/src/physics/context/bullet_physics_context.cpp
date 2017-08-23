#include "physics/context/bullet_physics_context.h"

namespace ifx{

bool BulletPhysicsContext::Init() {
    return true;
}

bool BulletPhysicsContext::Terminate() {
    return true;
}

void* BulletPhysicsContext::NativeData(){
    return nullptr;
}

}
