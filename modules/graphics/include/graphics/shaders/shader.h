#ifndef DUCK_SHADER_H
#define DUCK_SHADER_H

#include <string>

typedef unsigned int GLuint;

struct ShaderError{
    bool error_occured;
    std::string message;
};

class Shader {
public:

    Shader(std::string vertexShaderSource,
           std::string file_path);
    Shader(const Shader& other);

    virtual ~Shader();

    std::string file_path() const {return file_path_;}
    const std::string& shader_source() const {return shaderSource;}

    /*
     * compile function has to be called before using shader
     */
    void compile();

    /*
     * Used after linking with the progam.
     */
    void deleteShader();

    ShaderError Reload();

    GLuint getKey();

    std::string getSource();
protected:
    /*
     * Creates a shader: Vertex/Fragmet/Geometry
     */
    virtual GLuint createShader() = 0;

private:
    ShaderError CompileAndCheckError();

    void Compile(GLuint& id);
    void Delete(GLuint& id);

    GLuint id;
    std::string shaderSource;
    std::string last_compiled_shader_source_;
    std::string file_path_;
};


#endif //DUCK_SHADER_H
