#include "physics/rigid_body_tmp.h"

#include <physics/impl/rigid_body_impl.h>

namespace ifx {

RigidBodyTMP::RigidBodyTMP(std::unique_ptr<RigidBodyImpl> rigid_body_impl,
                           const RigidBodyParams&& params) :
        rigid_body_impl_(std::move(rigid_body_impl)),
        collision_shape_(params.collision_shape),
        mass_(params.mass){
    rigid_body_impl_->InitImpl(collision_shape_, mass_);
}

RigidBodyTMP::~RigidBodyTMP(){}

void* RigidBodyTMP::GetNativeRigidBody(){
    return rigid_body_impl_->GetNativeRigidBody();
}

}
