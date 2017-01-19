#ifndef PROJECT_BULLET_FRACTURE_PHYSICS_SIMULATION_H
#define PROJECT_BULLET_FRACTURE_PHYSICS_SIMULATION_H

#include <physics/simulations/bullet_physics_simulation.h>

namespace ifx {

class SceneContainer;

class BulletFracturePhysicsSimulation : public BulletPhysicsSimulation{
public:

    BulletFracturePhysicsSimulation(
            const BulletPhysicsSimulationCreateParams& params,
            std::shared_ptr<SceneContainer> scene);
    ~BulletFracturePhysicsSimulation();

private:
    std::shared_ptr<SceneContainer> scene_;
    
};
}

#endif //PROJECT_BULLET_FRACTURE_PHYSICS_SIMULATION_H
