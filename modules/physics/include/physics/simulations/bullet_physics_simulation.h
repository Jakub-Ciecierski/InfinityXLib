#ifndef PROJECT_BULLET_PHYSICS_SIMULATION_H
#define PROJECT_BULLET_PHYSICS_SIMULATION_H

#include "physics/physics_simulation.h"

#include <memory>

class btBroadphaseInterface;
class btBroadphaseInterface;
class btCollisionDispatcher;
class btConstraintSolver;
class btDefaultCollisionConfiguration;
class btDynamicsWorld;

namespace ifx {

struct BulletPhysicsSimulationCreateParams {
    std::shared_ptr<btBroadphaseInterface> broadphase;
    std::shared_ptr<btCollisionDispatcher> dispatcher;
    std::shared_ptr<btConstraintSolver> solver;
    std::shared_ptr<btDefaultCollisionConfiguration> collision_configuration;
    std::shared_ptr<btDynamicsWorld> dynamics_world;
};

class BulletPhysicsSimulation : public PhysicsSimulation {
public:
    BulletPhysicsSimulation(
        std::shared_ptr<PhysicsContext> physics_context,
        const BulletPhysicsSimulationCreateParams &params);
    ~BulletPhysicsSimulation() = default;

    virtual bool Terminate() override;

    std::shared_ptr<btDynamicsWorld> dynamics_world_bt() {
        return dynamics_world_;
    }

    virtual void Add(std::shared_ptr<RigidBody> rigid_body) override;
    virtual bool Remove(std::shared_ptr<RigidBody> rigid_body) override;

    virtual std::unique_ptr<RigidBodyImpl> CreateRigidBodyImpl() override;

    virtual void SetGravity(const glm::vec3 &g) override;
    virtual glm::vec3 GetGravity() override;

    virtual void AddImpulse() override;
protected:
    void UpdateFixedContent() override;

private:
    /**
     * Synchronizes transform of game object and rigid bodies
     */
    void SynchronizeRigidBodiesTransform();
    void SynchronizeGameObjectsTransform();

    std::shared_ptr<btBroadphaseInterface> broadphase_;
    std::shared_ptr<btCollisionDispatcher> dispatcher_;
    std::shared_ptr<btConstraintSolver> solver_;
    std::shared_ptr<btDefaultCollisionConfiguration> collision_configuration_;
    std::shared_ptr<btDynamicsWorld> dynamics_world_;

};
}

#endif //PROJECT_BULLET_PHYSICS_SIMULATION_H
