#include "physics/factory/bullet_physics_simulation_factory.h"

#include <physics/physics_simulation.h>
#include <physics/simulations/bullet_physics_simulation.h>
#include "physics/soft_body/simulation/soft_body_fem_simulation.h"

#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>

namespace ifx {

BulletPhysicsSimulationFactory::BulletPhysicsSimulationFactory() :
    dynamic_world_type_(DynamicWorldType::DISCRETE) {}

BulletPhysicsSimulationFactory::~BulletPhysicsSimulationFactory() {}

std::shared_ptr<PhysicsSimulation> BulletPhysicsSimulationFactory::Create(
    std::shared_ptr<PhysicsContext> physics_context) {
    auto create_params = CreateBulletDynamics();
    auto physics_simulation = std::make_shared<BulletPhysicsSimulation>(
        physics_context, *create_params);
    return physics_simulation;
}

BulletPhysicsSimulationFactory &
BulletPhysicsSimulationFactory::SetDynamicWorldType(DynamicWorldType type) {
    dynamic_world_type_ = type;
    return *this;
}

std::shared_ptr<BulletPhysicsSimulationCreateParams>
BulletPhysicsSimulationFactory::CreateBulletDynamics() {
    auto create_params
        = std::shared_ptr<BulletPhysicsSimulationCreateParams>(
            new BulletPhysicsSimulationCreateParams());
    create_params->collision_configuration
        = std::shared_ptr<btDefaultCollisionConfiguration>(
        new btDefaultCollisionConfiguration());

    create_params->dispatcher = std::shared_ptr<btCollisionDispatcher>(
        new btCollisionDispatcher(create_params->collision_configuration
                                      .get()));

    create_params->broadphase =
        std::shared_ptr<btDbvtBroadphase>(new btDbvtBroadphase());

    create_params->solver =
        std::shared_ptr<btSequentialImpulseConstraintSolver>(
            new btSequentialImpulseConstraintSolver());
    switch (dynamic_world_type_) {
        case DynamicWorldType::DISCRETE:
            create_params->dynamics_world
                = CreateDiscreteDynamicWorld(create_params);
            break;
        case DynamicWorldType::FRACTURE:
            create_params->dynamics_world
                = CreateDiscreteDynamicWorld(create_params);
            break;
    }
    return create_params;
}

std::shared_ptr<btDiscreteDynamicsWorld>
BulletPhysicsSimulationFactory::CreateDiscreteDynamicWorld(
    const std::shared_ptr<BulletPhysicsSimulationCreateParams> params) {
    return std::shared_ptr<btDiscreteDynamicsWorld>(
        new btDiscreteDynamicsWorld(
            params->dispatcher.get(),
            params->broadphase.get(),
            params->solver.get(),
            params->collision_configuration.get()));
}

}