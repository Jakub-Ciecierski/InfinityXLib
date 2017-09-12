#ifndef DUCK_PROGRAM_H
#define DUCK_PROGRAM_H

#include "graphics/shaders/shaders/fragment_shader.h"
#include "graphics/shaders/shaders/vertex_shader.h"
#include "graphics/shaders/shaders/geometry_shader.h"
#include "graphics/shaders/shaders/tess_control_shader.h"
#include "graphics/shaders/shaders/tess_eval_shader.h"

#include <resources/resource.h>

#include <memory>

namespace ifx {

class ProgramCreator;

struct Shaders {
    VertexShader *vertexShader = nullptr;
    FragmentShader *fragmentShader = nullptr;
    GeometryShader *geometryShader = nullptr;
    TessControlShader *tessControlShader = nullptr;
    TessEvalShader *tessEvalShader = nullptr;
};

enum class ShaderType {
    Vertex, Fragment, Geometry, TessControl, TessEvaluation
};

/*
 * This class encapsulates all shaders and is used to draw Meshes
 */
class Program : public ifx::Resource {
public:
    friend class ProgramCreator;

    ~Program();

    VertexShader *vertex_shader() { return vertex_shader_.get(); }
    FragmentShader *fragment_shader() { return fragment_shader_.get(); }
    GeometryShader *geometry_shader() { return geometry_shader_.get(); }
    TessControlShader *tess_control_shader() {
        return tess_control_shader_.get();
    }
    TessEvalShader *tess_eval_shader() { return tess_eval_shader_.get(); }

    void use() const;

    ShaderError Reload();

    GLuint getID() const;

    static std::string GetProgramPath(Shaders &shaders);

private:
    Program(Shaders shaders);

    ShaderError linkShaders();

    GLuint id;

    std::unique_ptr<VertexShader> vertex_shader_;
    std::unique_ptr<FragmentShader> fragment_shader_;
    std::unique_ptr<GeometryShader> geometry_shader_;
    std::unique_ptr<TessControlShader> tess_control_shader_;
    std::unique_ptr<TessEvalShader> tess_eval_shader_;

};
}

#endif //DUCK_PROGRAM_H
