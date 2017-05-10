#include "controls/controller/controller.h"

#include <controls/controller/controller_event.h>

namespace ifx {

Controller::Controller(){}

Controller::~Controller(){}

void Controller::Update(float){
    for(auto& event : events())
        event->Reset();
}

}