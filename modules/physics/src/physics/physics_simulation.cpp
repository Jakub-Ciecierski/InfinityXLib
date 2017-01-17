#include "physics/physics_simulation.h"

namespace ifx {

PhysicsSimulation::PhysicsSimulation() :
        is_running_(true){}
PhysicsSimulation::~PhysicsSimulation(){}

void PhysicsSimulation::Play(){
    is_running_ = true;
}
void PhysicsSimulation::Pause(){
    is_running_ = false;
}


void PhysicsSimulation::Add(std::shared_ptr<RigidBody> rigid_body){
    rigid_bodies_.push_back(rigid_body);
}

bool PhysicsSimulation::Remove(std::shared_ptr<RigidBody> rigid_body){
    for(unsigned int i = 0; i < rigid_bodies_.size(); i++){
        if(rigid_bodies_[i] == rigid_body){
            rigid_bodies_.erase(rigid_bodies_.begin() + i);
            return true;
        }
    }
    return false;
}

}