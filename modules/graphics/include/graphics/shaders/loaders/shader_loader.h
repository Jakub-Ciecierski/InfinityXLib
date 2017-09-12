#ifndef DUCK_SHADER_LOADER_H
#define DUCK_SHADER_LOADER_H

#include <graphics/shaders/shader.h>
#include <graphics/shaders/shaders/fragment_shader.h>
#include <graphics/shaders/shaders/geometry_shader.h>
#include <graphics/shaders/shaders/vertex_shader.h>
#include <graphics/shaders/shaders/tess_control_shader.h>
#include <graphics/shaders/shaders/tess_eval_shader.h>

typedef char GLchar;

/*
 * Logic behind loading Shaders from files
 */
class ShaderLoader {
public:

    ShaderLoader();

    ~ShaderLoader();

    std::string getShaderCode(const GLchar *path);

    VertexShader *loadVertexShader(const GLchar *path);
    GeometryShader *loadGeometryShader(const GLchar *path);
    FragmentShader *loadFragmentShader(const GLchar *path);
    TessControlShader *loadTessControlShader(const GLchar *path);
    TessEvalShader *loadTessEvalShader(const GLchar *path);
};

#endif //DUCK_SHADER_LOADER_H
