#include "graphics/shaders/program_creator.h"

#include <resources/resource_manager.h>
#include <resources/resource_memory_cache.h>

namespace ifx {

ProgramCreator::ProgramCreator(
        std::shared_ptr<ResourceManager> resource_manager) :
        resource_manager_(resource_manager){}

ProgramCreator::~ProgramCreator(){}

std::shared_ptr<Program> ProgramCreator::MakeProgram(Shaders& shaders){
    std::shared_ptr<Program> program
            = std::static_pointer_cast<Program>(
                    resource_manager_->resource_memory_cache()->Get(
                            Program::GetProgramPath(shaders)
                    ));
    if(!program){
        program = std::shared_ptr<Program>(new Program(shaders));
    }
    resource_manager_->resource_memory_cache()->Add(program);

    return program;
}

};