#include "physics/soft_body/soft_body_collisions/soft_body_collider.h"

#include <physics/rigid_body/rigid_body.h>

namespace ifx {

template<class T>
SoftBodyCollider<T>::SoftBodyCollider(std::shared_ptr<RigidBody> collider,
                                      const SoftBodyColliderData<T>& data) :
    collider_(collider),
    data_(data){
    collider_->SetIsKinematic(true);
    collider_->SetUserData((void*)&data_);
}

template
class SoftBodyCollider<double>;
template
class SoftBodyCollider<float>;


}