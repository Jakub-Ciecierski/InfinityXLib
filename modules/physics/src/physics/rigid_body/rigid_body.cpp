#include "physics/rigid_body/rigid_body.h"

namespace ifx {

RigidBody::RigidBody(std::unique_ptr<RigidBodyImpl> rigid_body_impl,
                     const RigidBodyParams &&params) :
    rigid_body_impl_(std::move(rigid_body_impl)){
    rigid_body_impl_->InitImpl(params.collision_shape,
                               params.mass,
                               params.physics_material);
}

void *RigidBody::GetNativeRigidBody() {
    return rigid_body_impl_->GetNativeRigidBody();
}

void RigidBody::Update(float time_delta) {
    Transformable::Update(time_delta);

    rigid_body_impl_->SetCollisionShapeScale(getScale());
}

}
