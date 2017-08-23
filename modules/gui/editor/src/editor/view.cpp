#include "editor/view.h"

namespace ifx{

View::View(std::string name) : name_(name){}

bool View::Terminate(){
    return true;
}

}