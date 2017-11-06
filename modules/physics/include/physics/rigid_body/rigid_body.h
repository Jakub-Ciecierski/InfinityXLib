#ifndef PROJECT_RIGID_BODY_TMP_H
#define PROJECT_RIGID_BODY_TMP_H

#include <memory>

#include <math/transform.h>

#include <physics/rigid_body/physics_material.h>
#include <physics/rigid_body/impl/rigid_body_impl.h>

namespace ifx {

class CollisionShape;

struct RigidBodyParams {
    std::shared_ptr<CollisionShape> collision_shape;

    float mass;

    PhysicsMaterial physics_material;
};

class RigidBody : public Transformable {
public:

    RigidBody(std::unique_ptr<RigidBodyImpl> rigid_body_impl,
              const RigidBodyParams &&params);
    ~RigidBody() = default;

    std::shared_ptr<CollisionShape> collision_shape(){
        return rigid_body_impl_->collision_shape();
    }

    float mass(){return rigid_body_impl_->mass();}
    void mass(float mass){rigid_body_impl_->mass(mass);}

    const PhysicsMaterial& physics_material() {
        return rigid_body_impl_->physics_material();
    }
    void physics_material(const PhysicsMaterial& physics_material) {
        rigid_body_impl_->physics_material(physics_material);
    }

    void *GetNativeRigidBody();

    virtual void Update(float time_delta = 0) override;
private:
    std::unique_ptr<RigidBodyImpl> rigid_body_impl_;

};
}

#endif //PROJECT_RIGID_BODY_TMP_H
