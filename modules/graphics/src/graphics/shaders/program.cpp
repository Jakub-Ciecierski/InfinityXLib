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

ShaderError Program::linkShaders() {
    ShaderError shader_error{false, ""};

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
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::string infoLogStr = infoLog;
        std::cout << infoLogStr << std::endl;
        shader_error = ShaderError{true, infoLogStr};
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

    return shader_error;
}

void Program::use() const {
    glUseProgram(id);
}

ShaderError Program::Reload() {
    if (vertex_shader_) {
        auto shader_error = vertex_shader_->Reload();
        if (shader_error.error_occured)
            return shader_error;
    }
    if (fragment_shader_) {
        auto shader_error = fragment_shader_->Reload();
        if (shader_error.error_occured)
            return shader_error;
    }
    if (geometry_shader_) {
        auto shader_error = geometry_shader_->Reload();
        if (shader_error.error_occured)
            return shader_error;
    }
    if (tess_control_shader_) {
        auto shader_error = tess_control_shader_->Reload();
        if (shader_error.error_occured)
            return shader_error;
    }
    if (tess_eval_shader_) {
        auto shader_error = tess_eval_shader_->Reload();
        if (shader_error.error_occured)
            return shader_error;
    }

    glDeleteProgram(id);

    return linkShaders();
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