#ifndef PROJECT_PHYSX_PHYSICS_SIMULATION_H
#define PROJECT_PHYSX_PHYSICS_SIMULATION_H

#include <physics/physics_simulation.h>

namespace ifx {

class PhysxPhysicsSimulation : public PhysicsSimulation {
public:

    PhysxPhysicsSimulation();

    ~PhysxPhysicsSimulation();

    void Update(float time_delta) override;

    void SetGravity(const glm::vec3 &g) override;

    glm::vec3 GetGravity() override;

    void AddImpulse() override;

    virtual std::unique_ptr<RigidBodyImpl> CreateRigidBodyImpl() override;
private:
};
}


#endif //PROJECT_PHYSX_PHYSICS_SIMULATION_H
