#include "common/updatable.h"

#include <GLFW/glfw3.h>

namespace ifx {

Updatable::Updatable() :
        is_running_(true){}

Updatable::Updatable(const UpdateTimeDelta& update_time_delta) :
    update_time_delta_(update_time_delta),
    is_running_(true){}

void Updatable::Update(float time_delta){
    UpdateTimersPre();
    if(!is_running_){
        return;
    }

    UpdateTimersPost();

    UpdateFixedContent();
}

bool Updatable::UpdateFixed(){
    UpdateTimersPre();
    if(!IsUpdateReady()){
        return false;
    }
    if(!is_running_){
        return false;
    }

    UpdateTimersPost();

    UpdateFixedContent();

    return true;
}

void Updatable::UpdateFixedContent(){

}

void Updatable::UpdateTimersPre() {
    auto current_time = glfwGetTime();
    auto last_elapsed = current_time - update_timer_.last_time;
    update_timer_.time_since_last_update += last_elapsed;
    update_timer_.last_time_since_last_update =
            update_timer_.time_since_last_update;
    update_timer_.last_time = current_time;
}

void Updatable::UpdateTimersPost(){
    update_timer_.iterations++;
    update_timer_.total_time += update_timer_.last_time_since_last_update;
}

bool Updatable::IsUpdateReady(){
    if (update_timer_.time_since_last_update >= update_time_delta_.time_delta) {
        update_timer_.time_since_last_update = 0.0f;
        return true;
    }
    return false;
}

void Updatable::ResetTimers(){
    update_timer_.total_time = 0;
    update_timer_.iterations = 0;
}

void Updatable::Pause(){
    is_running_ = false;
}

void Updatable::Play(){
    is_running_ = true;
}

}