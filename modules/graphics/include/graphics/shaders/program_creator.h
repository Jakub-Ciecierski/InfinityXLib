#ifndef PROJECT_PROGRAM_CREATOR_H
#define PROJECT_PROGRAM_CREATOR_H

#include <graphics/shaders/program.h>

namespace ifx {

class ResourceManager;

class ProgramCreator {
public:

    ProgramCreator(std::shared_ptr<ResourceManager>);

    ~ProgramCreator();

    std::shared_ptr<ResourceManager> resource_manager() {
        return resource_manager_;
    }

    std::shared_ptr<Program> MakeProgram(Shaders &shaders);
private:

    std::shared_ptr<ResourceManager> resource_manager_;
};
}

#endif //PROJECT_PROGRAM_CREATOR_H
