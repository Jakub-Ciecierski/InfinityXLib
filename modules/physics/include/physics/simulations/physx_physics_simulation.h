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

    std::shared_ptr<RigidBodyTMP>
    CreatAndAdd(const RigidBodyParams &&params) override;

    void AddImpulse() override;

private:
};
}


#endif //PROJECT_PHYSX_PHYSICS_SIMULATION_H
