#ifndef PROJECT_BULLET_PHYSICS_SIMULATION_H
#define PROJECT_BULLET_PHYSICS_SIMULATION_H

#include "physics/physics_simulation.h"

#include <memory>

class btBroadphaseInterface;
class btBroadphaseInterface;
class btCollisionDispatcher;
class btConstraintSolver;
class btDefaultCollisionConfiguration;
class btDiscreteDynamicsWorld;

namespace ifx {

class BulletPhysicsSimulation : public PhysicsSimulation {
public:
    BulletPhysicsSimulation();
    ~BulletPhysicsSimulation();

    virtual void Add(std::shared_ptr<RigidBody> rigid_body) override;
    virtual bool Remove(std::shared_ptr<RigidBody> rigid_body) override;

    virtual void Update(float time_delta) override;
    virtual void SetGravity(const glm::vec3& g) override;

private:
    /**
     * Synchronizes transform of game object and rigid bodies
     */
    void SynchronizeRigidBodiesTransform();
    void SynchronizeGameObjectsTransform();

    void Init();
    void InitEmptyDynamicsWorld();

    std::shared_ptr<btBroadphaseInterface> broadphase_;
    std::shared_ptr<btCollisionDispatcher> dispatcher_;
    std::shared_ptr<btConstraintSolver> solver_;
    std::shared_ptr<btDefaultCollisionConfiguration> collision_configuration_;
    std::shared_ptr<btDiscreteDynamicsWorld> dynamics_world_;

};
}

#endif //PROJECT_BULLET_PHYSICS_SIMULATION_H
