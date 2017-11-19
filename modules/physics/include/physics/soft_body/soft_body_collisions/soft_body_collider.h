#ifndef PROJECT_SOFT_BODY_COLLIDER_H
#define PROJECT_SOFT_BODY_COLLIDER_H

#include <memory>

#include <physics/soft_body/soft_body_collisions/soft_body_collider_data.h>

namespace ifx {

class RigidBody;

template<class T>
class SoftBodyCollider {
public:
    SoftBodyCollider(std::shared_ptr<RigidBody> collider,
                     const SoftBodyColliderData<T>& data);

    ~SoftBodyCollider() = default;

    std::shared_ptr<RigidBody> collider() { return collider_; }

    const SoftBodyColliderData<T>& data(){return data_;}

private:
    std::shared_ptr<RigidBody> collider_;
    SoftBodyColliderData<T> data_;
};

}

#endif //PROJECT_SOFT_BODY_COLLIDER_H
