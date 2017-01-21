#include <GLFW/glfw3.h>
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

void Simulation::Reset(){
    time_data_.total_time = 0.0f;
    time_data_.current_time = 0.0f;
    time_data_.time_since_last_update = 0.0f;
    time_data_.last_time = glfwGetTime();
    time_data_.simulation_length = -1.0f;
}

bool Simulation::UpdateTime(){
    time_data_.current_time = glfwGetTime();
    if(!running_){
        time_data_.last_time = time_data_.current_time;
        return false;
    }
    double elapsed = time_data_.current_time - time_data_.last_time;
    time_data_.time_since_last_update += elapsed;
    time_data_.total_time += elapsed;
    time_data_.last_time = time_data_.current_time;

    if(time_data_.total_time > time_data_.simulation_length){
        if(time_data_.simulation_length != -1.0f){
            SetRunning(false);
            return false;
        }
    }
    if(time_data_.time_since_last_update >= time_data_.time_delta){
        time_data_.time_since_last_update = 0.0f;
        return true;
    }
}

}