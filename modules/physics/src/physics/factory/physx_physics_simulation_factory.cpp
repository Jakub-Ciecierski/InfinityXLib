#include "physics/factory/physx_physics_simulation_factory.h"

#include <physics/simulations/physx_physics_simulation.h>
#include <physics/physics_simulation.h>
#include "physics/context/physx_context.h"
#include "physics/soft_body/simulation/soft_body_fem_simulation.h"
#include <physics/simulations/physx/physx_event_callback.h>

#include <common/unique_ptr.h>

#define _DEBUG // Physx requires that for some reason
#include <PxPhysicsAPI.h>

namespace ifx {

std::shared_ptr<PhysicsSimulation> PhysxPhysicsSimulationFactory::Create(
    std::shared_ptr<PhysicsContext> physics_context) {
    auto physx_context = std::dynamic_pointer_cast<PhysxContext>(
        physics_context);
    if (!physx_context)
        throw std::invalid_argument("Wrong PhysicsContext");

    auto event_callback = make_unique<PhysXEventCallback>();

    physx::PxSceneDesc sceneDesc(
        physx_context->px_physics()->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    physx::PxDefaultCpuDispatcher *px_dispatcher
        = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = px_dispatcher;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    auto CollisionFilterShader = [] (
        physx::PxFilterObjectAttributes /*attributes0*/,
        physx::PxFilterData /*filterData0*/,
        physx::PxFilterObjectAttributes /*attributes1*/,
        physx::PxFilterData /*filterData1*/,
        physx::PxPairFlags& retPairFlags, const void* /*constantBlock*/,
        physx::PxU32 /*constantBlockSize*/) -> physx::PxFilterFlags {
        retPairFlags = physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
        return physx::PxFilterFlag::eNOTIFY;
    };
    sceneDesc.filterShader = CollisionFilterShader;

    physx::PxScene *px_scene =
        physx_context->px_physics()->createScene(sceneDesc);
    //px_scene->setFlag(physx::PxSceneFlag::eENABLE_KINEMATIC_PAIRS, true);
    //px_scene->setFlag(physx::PxSceneFlag::eENABLE_KINEMATIC_STATIC_PAIRS,true);
    px_scene->setSimulationEventCallback(event_callback.get());

    std::shared_ptr<PhysicsSimulation> simulation
        = std::make_shared<PhysxPhysicsSimulation>(
            physics_context,
            px_dispatcher,
            px_scene,
            std::move(event_callback)
        );

    return simulation;
}
}