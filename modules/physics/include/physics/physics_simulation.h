#ifndef PROJECT_PHYSICS_SIMULATION_H
#define PROJECT_PHYSICS_SIMULATION_H

#include <memory>
#include <vector>

#include <math/math_ifx.h>
#include <common/updatable.h>

namespace ifx {

class RigidBody;
class RigidBodyImpl;
struct RigidBodyParams;
class PhysicsContext;

template<class T>
class SoftBodyFEM;

template<class T>
class SoftBodyFEMSimulation;

class PhysicsSimulation : public Updatable {
public:
    PhysicsSimulation(std::shared_ptr<PhysicsContext> physics_context);
    virtual ~PhysicsSimulation() = default;

    SoftBodyFEMSimulation<double>& soft_body_fem_simulation(){
        return *soft_body_fem_simulation_;
    };

    virtual void SetGravity(const glm::vec3 &g) = 0;
    virtual glm::vec3 GetGravity() = 0;

    virtual bool Terminate() = 0;

    virtual void AddImpulse() = 0;

    virtual void Add(std::shared_ptr<RigidBody> rigid_body);
    virtual bool Remove(std::shared_ptr<RigidBody> rigid_body);

    void Add(std::shared_ptr<SoftBodyFEM<double>> soft_body);
    bool Remove(std::shared_ptr<SoftBodyFEM<double>> soft_body);

    virtual std::unique_ptr<RigidBodyImpl> CreateRigidBodyImpl() = 0;

protected:
    virtual void UpdateFixedContent() override;

    std::shared_ptr<PhysicsContext> physics_context_;

    std::vector<std::shared_ptr<RigidBody>> rigid_bodies_;

private:
    std::unique_ptr<SoftBodyFEMSimulation<double>> soft_body_fem_simulation_;
};
}

#endif //PROJECT_PHYSICS_SIMULATION_H
