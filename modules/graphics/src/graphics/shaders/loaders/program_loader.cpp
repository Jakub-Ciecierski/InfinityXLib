#include "graphics/shaders/loaders/program_loader.h"

#include <graphics/shaders/program_creator.h>

namespace ifx {

ProgramLoader::ProgramLoader(std::shared_ptr<ProgramCreator> program_creator) :
        program_creator_(program_creator) { }

ProgramLoader::~ProgramLoader() { }

std::shared_ptr<Program> ProgramLoader::CreateProgram(const ShaderPaths& shader_paths){
    Shaders shaders;

    if(shader_paths.vertex_path != ""){
        shaders.vertexShader =
                shaderLoader.loadVertexShader(shader_paths.vertex_path.c_str());
        shaders.vertexShader->compile();
    }
    if(shader_paths.fragment_path != ""){
        shaders.fragmentShader =
                shaderLoader.loadFragmentShader(shader_paths.fragment_path.c_str());
        shaders.fragmentShader->compile();
    }
    if(shader_paths.geometry_path!= ""){
        shaders.geometryShader =
                shaderLoader.loadGeometryShader(shader_paths.geometry_path.c_str());
        shaders.geometryShader->compile();
    }
    if(shader_paths.tcs_path!= ""){
        shaders.tessControlShader =
                shaderLoader.loadTessControlShader(shader_paths.tcs_path.c_str());
        shaders.tessControlShader->compile();
    }
    if(shader_paths.tes_path!= ""){
        shaders.tessEvalShader =
                shaderLoader.loadTessEvalShader(shader_paths.tes_path.c_str());
        shaders.tessEvalShader->compile();
    }

    return program_creator_->MakeProgram(shaders);
}

std::shared_ptr<Program> ProgramLoader::CreateProgram(std::string vertex_path,
                                                      std::string fragment_path) {
    VertexShader *vertexShader =
            shaderLoader.loadVertexShader(vertex_path.c_str());
    FragmentShader *fragmentShader =
            shaderLoader.loadFragmentShader(fragment_path.c_str());

    vertexShader->compile();
    fragmentShader->compile();

    Shaders shaders;
    shaders.vertexShader = vertexShader;
    shaders.fragmentShader = fragmentShader;

    return program_creator_->MakeProgram(shaders);
}

std::shared_ptr<Program> ProgramLoader::CreateProgram(std::string vertex_path,
                                                      std::string fragment_path,
                                                      std::string geometry_path) {
    VertexShader *vertexShader =
            shaderLoader.loadVertexShader(vertex_path.c_str());
    FragmentShader *fragmentShader =
            shaderLoader.loadFragmentShader(fragment_path.c_str());
    GeometryShader *geometryShader =
            shaderLoader.loadGeometryShader(geometry_path.c_str());

    vertexShader->compile();
    fragmentShader->compile();
    geometryShader->compile();

    Shaders shaders;
    shaders.vertexShader = vertexShader;
    shaders.fragmentShader = fragmentShader;
    shaders.geometryShader = geometryShader;

    return program_creator_->MakeProgram(shaders);
}

std::shared_ptr<Program> ProgramLoader::CreateProgram(std::string vertex_path,
                                                      std::string fragment_path,
                                                      std::string tcs_path,
                                                      std::string tes_path) {
    VertexShader *vertexShader =
            shaderLoader.loadVertexShader(vertex_path.c_str());
    FragmentShader *fragmentShader =
            shaderLoader.loadFragmentShader(fragment_path.c_str());
    TessControlShader *tessControlShader =
            shaderLoader.loadTessControlShader(tcs_path.c_str());
    TessEvalShader *tessEvalShader =
            shaderLoader.loadTessEvalShader(tes_path.c_str());

    vertexShader->compile();
    fragmentShader->compile();
    tessControlShader->compile();
    tessEvalShader->compile();

    Shaders shaders;
    shaders.vertexShader = vertexShader;
    shaders.fragmentShader = fragmentShader;
    shaders.tessControlShader = tessControlShader;
    shaders.tessEvalShader = tessEvalShader;

    return program_creator_->MakeProgram(shaders);
}
}