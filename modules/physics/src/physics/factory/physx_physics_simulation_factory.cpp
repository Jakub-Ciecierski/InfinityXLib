#include "physics/factory/physx_physics_simulation_factory.h"

#include <physics/simulations/physx_physics_simulation.h>
#include <physics/physics_simulation.h>
#include <common/unique_ptr.h>

#define _DEBUG // Physx requires that for some reason
#include <PxPhysicsAPI.h>

#define PVD_HOST "127.0.0.1"

namespace ifx {

PhysxPhysicsSimulationFactory::PhysxPhysicsSimulationFactory() {

}

PhysxPhysicsSimulationFactory::~PhysxPhysicsSimulationFactory() {

}

std::shared_ptr<PhysicsSimulation> PhysxPhysicsSimulationFactory::Create() {
    auto px_allocator_callback = ifx::make_unique<physx::PxDefaultAllocator>();
    auto px_error_callback = ifx::make_unique<physx::PxDefaultErrorCallback>();

    auto px_foundation
            = PxCreateFoundation(PX_FOUNDATION_VERSION,
                                 *px_allocator_callback, *px_error_callback);
    if(!px_foundation)
        throw std::invalid_argument("PxCreateFoundation Failed");

    // Visual debugger.
    auto px_pvd = physx::PxCreatePvd(*px_foundation);

    auto px_transport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST,
                                                              5425, 10);
    px_pvd->connect(*px_transport, physx::PxPvdInstrumentationFlag::eALL);

    auto px_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *px_foundation,
                                   physx::PxTolerancesScale(),
                                   true, px_pvd);
    if(!px_physics)
        throw std::invalid_argument("PxCreatePhysics Failed");

    physx::PxSceneDesc sceneDesc(px_physics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    physx::PxDefaultCpuDispatcher* px_dispatcher
            = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher	= px_dispatcher;
    sceneDesc.filterShader	= physx::PxDefaultSimulationFilterShader;
    physx::PxScene* px_scene = px_physics->createScene(sceneDesc);

    std::shared_ptr<PhysicsSimulation> simulation
            = std::make_shared<PhysxPhysicsSimulation>(
                    px_physics,
                    px_pvd,
                    px_transport,
                    px_foundation,
                    std::move(px_allocator_callback),
                    std::move(px_error_callback),
                    px_dispatcher,
                    px_scene
            );

    return simulation;
}
}