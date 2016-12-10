#include "vr/simulation.h"

namespace ifx {

Simulation::Simulation() : running_(true){}
Simulation::~Simulation(){}

bool Simulation::IsRunning(){
    return running_;
}
void Simulation::SetRunning(bool value){
    running_ = value;
}

void Simulation::Play(){
    running_ = true;
}
void Simulation::Pause(){
    running_ = false;
}

}