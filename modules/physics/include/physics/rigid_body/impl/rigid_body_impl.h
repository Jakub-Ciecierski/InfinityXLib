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

class RigidBodyImpl {
public:

    RigidBodyImpl();

    virtual ~RigidBodyImpl() = default;

    virtual void *GetNativeRigidBody() = 0;

    virtual void InitImpl(
        std::shared_ptr<CollisionShape> collision_shape,
        float mass,
        const PhysicsMaterial& physics_material) = 0;
    virtual void InitCollisionShape(const StaticPlaneShape *shape) = 0;
    virtual void InitCollisionShape(const BoxCollisionShape *shape) = 0;
    virtual void InitCollisionShape(const SphereCollisionShape *shape) = 0;

    virtual void SetCollisionShapeScale(const glm::vec3 &scale) = 0;

    virtual bool IsDynamic() = 0;
protected:
    std::shared_ptr<CollisionShape> collision_shape_;
    float mass_;
    PhysicsMaterial physics_material_;

private:
};
}

#endif //PROJECT_RIGIDBODYIMPL_H
