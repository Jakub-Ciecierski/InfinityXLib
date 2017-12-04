#include "physics/soft_body/soft_body_collisions/soft_body_collider_data.h"

#include "physics/simulations/physx/physx_event_callback.h"

#include <iostream>

#include <math/math_ifx.h>

#define _DEBUG
#include <PxPhysicsAPI.h>

namespace ifx {

void PhysXEventCallback::onContact(
    const physx::PxContactPairHeader &pairHeader,
    const physx::PxContactPair *pairs,
    physx::PxU32 nbPairs) {
    void* user_data = nullptr;
    auto user_data1 = pairHeader.actors[0]->userData;
    auto user_data2 = pairHeader.actors[1]->userData;

    float impulse_director = 1;

    if(!user_data1 && !user_data2){
        std::cout << "onContact: both actors are rigid bodies" << std::endl;
    }
    else if(user_data1 && !user_data2){
        impulse_director = 1;
        std::cout << "onContact: actor1 is soft body" << std::endl;
        user_data = user_data1;
    }
    else if(!user_data1 && user_data2){
        impulse_director = -1;
        std::cout << "onContact: actor2 is soft body" << std::endl;
        user_data = user_data2;
    }
    else if(user_data1 && user_data2){
        std::cout << "onContact: both actors are soft bodies" << std::endl;
    }

    std::cout << "onContact: nbPairs:" << nbPairs << std::endl;

    if(user_data) {
        auto soft_body_collider_data =
            static_cast<SoftBodyColliderData<double> *>(user_data);
        std::cout << "Vertex ID: "
                  << soft_body_collider_data->vertex_id()
                  << std::endl;

        const physx::PxU32 bufferSize = 64;
        physx::PxContactPairPoint contacts[bufferSize];
        for (physx::PxU32 i = 0; i < nbPairs; i++) {
            physx::PxU32 nbContacts = pairs[i].extractContacts(contacts,
                                                               bufferSize);
            std::cout << "onContact: nbContacts:" << nbContacts << std::endl;
            for (physx::PxU32 j = 0; j < nbContacts; j++) {
                auto &normal = contacts[j].normal;
                auto &impulse = contacts[j].impulse;

                std::cout
                    << "normal: "
                    << normal.x << ", "
                    << normal.y << ", "
                    << normal.z << std::endl;
                std::cout
                    << "impulse norm: "
                    << impulse.x << ", "
                    << impulse.y << ", "
                    << impulse.z << std::endl;

                auto ifx_impulse = glm::vec3(impulse.x,
                                             impulse.y,
                                             impulse.z);

                auto impulse_magnitude = impulse_director * ifx_impulse.length();
                auto impulse_normal = glm::normalize(ifx_impulse);
                soft_body_collider_data->HandleCollision(impulse_normal,
                                                         impulse_magnitude);
            }
        }
    }


    std::cout << std::endl;
}

void PhysXEventCallback::onConstraintBreak(
    physx::PxConstraintInfo *constraints,
    physx::PxU32 count) {

}

void PhysXEventCallback::onWake(physx::PxActor **actors, physx::PxU32 count) {

}

void PhysXEventCallback::onSleep(physx::PxActor **actors, physx::PxU32 count) {

}

void PhysXEventCallback::onTrigger(physx::PxTriggerPair *pairs,
                                      physx::PxU32 count) {
}

void PhysXEventCallback::onAdvance(const physx::PxRigidBody *const *bodyBuffer,
                                   const physx::PxTransform *poseBuffer,
                                   const physx::PxU32 count) {

}

}