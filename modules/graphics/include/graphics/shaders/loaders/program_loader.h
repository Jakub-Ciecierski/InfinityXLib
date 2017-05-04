#ifndef DUCK_PROGRAM_LOADER_H
#define DUCK_PROGRAM_LOADER_H

#include <graphics/shaders/program.h>
#include <graphics/shaders/loaders/shader_loader.h>

#include <memory>

namespace ifx {
class ProgramCreator;


/*
 * Loads specific shaders compiled into Programs from resources
 */
class ProgramLoader {
public:
    ProgramLoader(std::shared_ptr<ProgramCreator> program_creator_);

    ~ProgramLoader();

    std::shared_ptr<Program> CreateProgram(std::string vertex_path,
                                           std::string fragment_path);

    std::shared_ptr<Program> CreateProgram(std::string vertex_path,
                                           std::string fragment_path,
                                           std::string geometry_path);

    std::shared_ptr<Program> CreateProgram(std::string vertex_path,
                                           std::string fragment_path,
                                           std::string tcs_path,
                                           std::string tes_path);

private:
    ShaderLoader shaderLoader;

    std::shared_ptr<ProgramCreator> program_creator_;

};
}

#endif //DUCK_PROGRAM_LOADER_H
