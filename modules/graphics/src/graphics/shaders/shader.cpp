#include "graphics/shaders/shader.h"

#include <iostream>
#include <stdexcept>
#include <graphics/shaders/loaders/shader_loader.h>

#include <GL/glew.h>

using namespace std;

Shader::Shader(string shaderSource,
               string file_path) :
        shaderSource(shaderSource),
        last_compiled_shader_source_(shaderSource),
        file_path_(file_path){
}

Shader::Shader(const Shader& other){
    id = other.id;
    shaderSource = other.shaderSource;
    last_compiled_shader_source_ = other.last_compiled_shader_source_;
    file_path_ = other.file_path_;
}

Shader::~Shader() {

}

void Shader::compile() {
    Compile(id);

}

void Shader::deleteShader() {
    Delete(id);
}

ShaderError Shader::Reload(){
    ShaderLoader shader_loader;

    shaderSource = shader_loader.getShaderCode(file_path_.c_str());
    std::string shader_source_tmp = shaderSource;

    auto shader_error = CompileAndCheckError();
    if(shader_error.error_occured){
        shaderSource = last_compiled_shader_source_;
    }else{
        last_compiled_shader_source_ = shaderSource;
    }

    deleteShader();
    compile();

    shaderSource = shader_source_tmp;

    return shader_error;
}

ShaderError Shader::CompileAndCheckError(){
    ShaderError shader_error{false, ""};

    GLuint test_id;
    try{
        Compile(test_id);
    }catch(const std::invalid_argument& e){
        shader_error.error_occured = true;
        shader_error.message = e.what();
    }
    Delete(test_id);

    return shader_error;
}

void Shader::Compile(GLuint& id){
    id = createShader();
    const GLchar* rawData = shaderSource.c_str();

    glShaderSource(id, 1, &(rawData), NULL);
    glCompileShader(id);

    // Check status;
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::string infoLogStr = infoLog;
        throw std::invalid_argument("ERROR::SHADER::COMPILATION_FAILED\n"
                                    + infoLogStr);
    }
}

void Shader::Delete(GLuint& id){
    glDeleteShader(id);
}

GLuint Shader::getKey() {
    return id;
}

std::string Shader::getSource(){
    return this->shaderSource;
}