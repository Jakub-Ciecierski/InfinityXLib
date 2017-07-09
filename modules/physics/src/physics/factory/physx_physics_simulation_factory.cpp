#include "physics/factory/physx_physics_simulation_factory.h"

#include <physics/simulations/physx_physics_simulation.h>
#include <physics/physics_simulation.h>

//#include <PxPhysicsAPI.h>

#define PVD_HOST "127.0.0.1"

namespace ifx {

PhysxPhysicsSimulationFactory::PhysxPhysicsSimulationFactory() {

}

PhysxPhysicsSimulationFactory::~PhysxPhysicsSimulationFactory() {

}

std::shared_ptr<PhysicsSimulation> PhysxPhysicsSimulationFactory::Create() {
    /*
    physx::PxAllocatorCallback allocator_callback;
    physx::PxErrorCallback error_callback;

    auto foundation
            = PxCreateFoundation(PX_FOUNDATION_VERSION,
                                 allocator_callback, error_callback);
    if(!foundation)
        throw std::invalid_argument("PxCreateFoundation Failed");

    // Visual debugger.
    auto pvd = physx::PxCreatePvd(*foundation);

    auto transport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST,
                                                              5425, 10);
    pvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

    auto physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation,
                                   physx::PxTolerancesScale(),
                                   true, pvd);
    if(!physics)
        throw std::invalid_argument("PxCreatePhysics Failed");

    std::shared_ptr<PhysicsSimulation> simulation
            = std::make_shared<PhysxPhysicsSimulation>();
    return simulation;*/
}
}