#ifndef PROJECT_PHYSICS_SIMULATION_H
#define PROJECT_PHYSICS_SIMULATION_H

#include <memory>
#include <vector>

#include <math/math_ifx.h>

namespace ifx {

class RigidBody;

class PhysicsSimulation {
public:
    PhysicsSimulation();
    virtual ~PhysicsSimulation();

    bool is_running(){return is_running_;}
    void is_running(bool v){is_running_ = v;}

    virtual void Update(float time_delta) = 0;

    virtual void SetGravity(const glm::vec3& g) = 0;
    virtual glm::vec3 GetGravity() = 0;

    virtual void AddImpulse() = 0;

    void Play();
    void Pause();

    virtual void Add(std::shared_ptr<RigidBody> rigid_body);
    virtual bool Remove(std::shared_ptr<RigidBody> rigid_body);

protected:
    std::vector<std::shared_ptr<RigidBody>> rigid_bodies_;

    bool is_running_;
};
}

#endif //PROJECT_PHYSICS_SIMULATION_H
