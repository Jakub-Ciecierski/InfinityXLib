#include "graphics/shaders/program.h"

#include <graphics/shaders/loaders/shader_loader.h>
#include <resources/resource_memory_cache.h>

#include <stdexcept>
#include <iostream>

#include <GL/glew.h>

namespace ifx {

Program::Program(Shaders shaders) :
        Resource(GetProgramPath(shaders), ifx::ResourceType::SHADER) {
    vertex_shader_.reset(shaders.vertexShader);
    fragment_shader_.reset(shaders.fragmentShader);
    geometry_shader_.reset(shaders.geometryShader);
    tess_control_shader_.reset(shaders.tessControlShader);
    tess_eval_shader_.reset(shaders.tessEvalShader);

    linkShaders();
}

Program::~Program() {
    glDeleteProgram(id);
}

void Program::linkShaders() {
    id = glCreateProgram();

    if (vertex_shader_)
        glAttachShader(id, vertex_shader_->getKey());
    if (fragment_shader_)
        glAttachShader(id, fragment_shader_->getKey());
    if (geometry_shader_)
        glAttachShader(id, geometry_shader_->getKey());
    if (tess_control_shader_)
        glAttachShader(id, tess_control_shader_->getKey());
    if (tess_eval_shader_)
        glAttachShader(id, tess_eval_shader_->getKey());

    glLinkProgram(id);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::string infoLogStr = infoLog;
        std::cout << infoLogStr << std::endl;

        throw new std::invalid_argument("ERROR::PROGRAM::COMPILATION_FAILED\n"
                                        + infoLogStr);
    }

    if (vertex_shader_)
        vertex_shader_->deleteShader();
    if (fragment_shader_)
        fragment_shader_->deleteShader();
    if (geometry_shader_)
        geometry_shader_->deleteShader();
    if (tess_control_shader_)
        tess_control_shader_->deleteShader();
    if (tess_eval_shader_)
        tess_eval_shader_->deleteShader();
}


void Program::use() const {
    glUseProgram(id);
}

void Program::Reload() {
    glDeleteProgram(id);

    if (vertex_shader_)
        vertex_shader_->Reload();
    if (fragment_shader_)
        fragment_shader_->Reload();
    if (geometry_shader_)
        geometry_shader_->Reload();
    if (tess_control_shader_)
        tess_control_shader_->Reload();
    if (tess_eval_shader_)
        tess_eval_shader_->Reload();

    linkShaders();
}

GLuint Program::getID() const {
    return id;
}

// static
std::string Program::GetProgramPath(Shaders &shaders) {
    std::string path = "";
    if (shaders.vertexShader)
        path += shaders.vertexShader->file_path();
    if (shaders.fragmentShader)
        path += shaders.fragmentShader->file_path();
    if (shaders.geometryShader)
        path += shaders.geometryShader->file_path();
    if (shaders.tessControlShader)
        path += shaders.tessControlShader->file_path();
    if (shaders.tessEvalShader)
        path += shaders.tessEvalShader->file_path();

    return path;
}
}