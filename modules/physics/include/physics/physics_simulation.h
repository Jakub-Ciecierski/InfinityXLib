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

class PhysicsSimulation : public Updatable{
public:
    PhysicsSimulation();
    virtual ~PhysicsSimulation();

    bool is_running(){return is_running_;}
    void is_running(bool v){is_running_ = v;}

    virtual void SetGravity(const glm::vec3& g) = 0;
    virtual glm::vec3 GetGravity() = 0;

    virtual void AddImpulse() = 0;

    void Play();
    void Pause();

    virtual void Add(std::shared_ptr<RigidBody> rigid_body);

    virtual bool Remove(std::shared_ptr<RigidBody> rigid_body);

    virtual std::unique_ptr<RigidBodyImpl> CreateRigidBodyImpl() = 0;

protected:
    std::vector<std::shared_ptr<RigidBody>> rigid_bodies_;

    bool is_running_;
};
}

#endif //PROJECT_PHYSICS_SIMULATION_H
