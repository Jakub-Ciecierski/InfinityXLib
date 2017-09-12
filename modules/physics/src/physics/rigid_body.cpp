#include "physics/rigid_body.h"

#include <physics/impl/rigid_body_impl.h>

namespace ifx {

RigidBody::RigidBody(std::unique_ptr<RigidBodyImpl> rigid_body_impl,
                     const RigidBodyParams &&params) :
    rigid_body_impl_(std::move(rigid_body_impl)),
    collision_shape_(params.collision_shape),
    mass_(params.mass) {
    rigid_body_impl_->InitImpl(collision_shape_, mass_);
}

RigidBody::~RigidBody() {}

void *RigidBody::GetNativeRigidBody() {
    return rigid_body_impl_->GetNativeRigidBody();
}

void RigidBody::Update(float time_delta) {
    Transformable::Update(time_delta);

    rigid_body_impl_->SetCollisionShapeScale(getScale());
}

}
