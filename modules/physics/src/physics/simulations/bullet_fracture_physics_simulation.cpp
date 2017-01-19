#include "physics/simulations/bullet_fracture_physics_simulation.h"

namespace ifx{

BulletFracturePhysicsSimulation::BulletFracturePhysicsSimulation(
        const BulletPhysicsSimulationCreateParams& params,
        std::shared_ptr<SceneContainer> scene)
        : BulletPhysicsSimulation(params),
          scene_(scene){}

BulletFracturePhysicsSimulation::~BulletFracturePhysicsSimulation(){}

}