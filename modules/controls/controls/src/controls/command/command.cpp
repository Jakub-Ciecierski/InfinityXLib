#include "controls/command/command.h"

namespace ifx {

Command::Command(const CommandExecutable&& executable) :
        executable_(executable) {}

Command::~Command(){}

void Command::Execute(){
    executable_.execute_fuction(executable_.controller,
                                executable_.object);
}

}