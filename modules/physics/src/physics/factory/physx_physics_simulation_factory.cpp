#include "physics/factory/physx_physics_simulation_factory.h"

#include <physics/simulations/physx_physics_simulation.h>
#include <physics/physics_simulation.h>
#include "physics/context/physx_context.h"

#include <common/unique_ptr.h>

#define _DEBUG // Physx requires that for some reason
#include <PxPhysicsAPI.h>

namespace ifx {

std::shared_ptr<PhysicsSimulation> PhysxPhysicsSimulationFactory::Create(
        std::shared_ptr<PhysicsContext> physics_context) {
    auto physx_context = std::dynamic_pointer_cast<PhysxContext>(
            physics_context);
    if(!physx_context)
        throw std::invalid_argument("Wrong PhysicsContext");

    physx::PxSceneDesc sceneDesc(
            physx_context->px_physics()->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    physx::PxDefaultCpuDispatcher* px_dispatcher
            = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher	= px_dispatcher;
    sceneDesc.filterShader	= physx::PxDefaultSimulationFilterShader;
    physx::PxScene* px_scene =
            physx_context->px_physics()->createScene(sceneDesc);

    std::shared_ptr<PhysicsSimulation> simulation
            = std::make_shared<PhysxPhysicsSimulation>(
                    physics_context,
                    px_dispatcher,
                    px_scene
            );

    return simulation;
}
}