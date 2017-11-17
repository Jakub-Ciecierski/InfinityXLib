#ifndef PROJECT_RIGIDBODYIMPL_H
#define PROJECT_RIGIDBODYIMPL_H

#include <memory>
#include <math/math_ifx.h>
#include <physics/rigid_body/physics_material.h>

namespace ifx {

class CollisionShape;
class StaticPlaneShape;
class BoxCollisionShape;
class SphereCollisionShape;
class MeshCollisionShape;

class RigidBodyImpl {
public:

    RigidBodyImpl();
    virtual ~RigidBodyImpl() = default;

    std::shared_ptr<CollisionShape> collision_shape(){
        return collision_shape_;
    }
    float mass(){return mass_;}
    void mass(float mass){
        if (IsDynamic() && mass <= 0) {
            return;
        }
        if (!IsDynamic()){
            return;
        }
        mass_ = mass;
        SetMass(mass_);
    }
    const PhysicsMaterial& physics_material() {return physics_material_;}
    void physics_material(const PhysicsMaterial& physics_material) {
        physics_material_ = physics_material;
        SetPhysicsMaterial(physics_material_);
    }

    virtual void *GetNativeRigidBody() = 0;

    virtual void InitImpl(
        std::shared_ptr<CollisionShape> collision_shape,
        float mass,
        const PhysicsMaterial& physics_material) = 0;
    virtual void InitCollisionShape(const StaticPlaneShape *shape) = 0;
    virtual void InitCollisionShape(const BoxCollisionShape *shape) = 0;
    virtual void InitCollisionShape(const SphereCollisionShape *shape) = 0;
    virtual void InitCollisionShape(const MeshCollisionShape *shape) = 0;

    virtual void SetCollisionShapeScale(const glm::vec3 &scale) = 0;

    virtual bool IsDynamic() = 0;

    virtual void SetMass(float mass) = 0;
    virtual void SetPhysicsMaterial(const PhysicsMaterial& physics_material) = 0;

    virtual void SetIsKinematic(bool is_kinematic) = 0;

protected:
    std::shared_ptr<CollisionShape> collision_shape_;
    float mass_;
    PhysicsMaterial physics_material_;

private:
};
}

#endif //PROJECT_RIGIDBODYIMPL_H
