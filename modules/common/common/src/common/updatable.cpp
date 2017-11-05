#include "common/updatable.h"

#include <GLFW/glfw3.h>

namespace ifx {

Updatable::Updatable(const UpdateTimeDelta& update_time_delta) :
    update_time_delta_(update_time_delta){}

void Updatable::Update(float time_delta){
    UpdateTimers();
}

bool Updatable::UpdateFixed(){
    UpdateTimers();
    if(!IsUpdateReady()){
        return false;
    }

    UpdateFixedContent();

    return true;
}

void Updatable::UpdateFixedContent(){

}

void Updatable::UpdateTimers() {
    update_timer_.current_time = glfwGetTime();

    double elapsed = update_timer_.current_time - update_timer_.last_time;
    update_timer_.time_since_last_update += elapsed;
    update_timer_.total_time += elapsed;
    update_timer_.last_time = update_timer_.current_time;
}

bool Updatable::IsUpdateReady(){
    if (update_timer_.time_since_last_update >= update_time_delta_.time_delta) {
        update_timer_.time_since_last_update = 0.0f;
        return true;
    }
    return false;
}

}