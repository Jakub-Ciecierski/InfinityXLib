#include "common/updatable.h"

#include <GLFW/glfw3.h>

namespace ifx {

Updatable::Updatable() :
        is_running_(true){}

Updatable::Updatable(const UpdateTimeDelta& update_time_delta) :
    update_time_delta_(update_time_delta),
    is_running_(true){}

void Updatable::Update(float time_delta){
    UpdateSynchronizationPre();
    if(!is_running_){
        timer_ = UpdateTimer{};
        return;
    }
    UpdateSynchronizationPost();

    UpdateFixedContentTimed();
}

bool Updatable::UpdateFixed(){
    UpdateSynchronizationPre();
    if(!IsUpdateReady()){
        return false;
    }
    if(!is_running_){
        timer_ = UpdateTimer{};
        return false;
    }
    UpdateSynchronizationPost();

    UpdateFixedContentTimed();

    return true;
}

void Updatable::UpdateFixedContentTimed(){
    timer_.Start();
    UpdateFixedContent();
    timer_.Stop();
}

void Updatable::UpdateFixedContent(){

}

void Updatable::UpdateSynchronizationPre() {
    auto current_time = glfwGetTime();
    auto last_elapsed = current_time - synchronization_timer_.last_time;
    synchronization_timer_.time_since_last_update += last_elapsed;
    synchronization_timer_.last_time_since_last_update =
            synchronization_timer_.time_since_last_update;
    synchronization_timer_.last_time = current_time;
}

void Updatable::UpdateSynchronizationPost(){
    synchronization_timer_.iterations++;
    synchronization_timer_.total_time += synchronization_timer_.last_time_since_last_update;
}

bool Updatable::IsUpdateReady(){
    if (synchronization_timer_.time_since_last_update >= update_time_delta_.time_delta) {
        synchronization_timer_.time_since_last_update = 0.0f;
        return true;
    }
    return false;
}

void Updatable::ResetTimers(){
    synchronization_timer_.total_time = 0;
    synchronization_timer_.iterations = 0;
}

void Updatable::Pause(){
    is_running_ = false;
}

void Updatable::Play(){
    is_running_ = true;
}

}