#ifndef PROJECT_PROGRAM_FACTORY_H
#define PROJECT_PROGRAM_FACTORY_H

#include <graphics/shaders/program.h>

#include <memory>

namespace ifx {

class ProgramCreator;

class ProgramFactory {
public:

    ProgramFactory(std::shared_ptr<ProgramCreator> program_creator);

    ~ProgramFactory();

    std::shared_ptr<Program> LoadMainProgram();
    std::shared_ptr<Program> LoadMainNormalMappingProgram();
    std::shared_ptr<Program> LoadHeightmapProgram();

    std::shared_ptr<Program> LoadShadowMappingProgram();

    std::shared_ptr<Program> LoadCAMMaterialBoxProgram();
    std::shared_ptr<Program> LoadCAMPlane();

    std::shared_ptr<Program> LoadInstancedProgram();

    std::shared_ptr<Program> LoadFBOProgram();
    std::shared_ptr<Program> LoadNormalVisionProgram();

    std::shared_ptr<Program> loadTessellationLODProgram();
    std::shared_ptr<Program> loadTessellationBicubicBezierPolygonProgram();
    std::shared_ptr<Program> loadTessellationBicubicBezierProgram();
    std::shared_ptr<Program> loadTessellationProgram();
    std::shared_ptr<Program> loadCubemapProgram();
    std::shared_ptr<Program> loadAllLightProgram();
    std::shared_ptr<Program> loadAnisotropicLightProgram();
    std::shared_ptr<Program> loadBumpMappingProgram();
    std::shared_ptr<Program> loadLampProgram();

private:
    std::shared_ptr<ProgramCreator> program_creator_;
};
}

#endif //PROJECT_PROGRAM_FACTORY_H
