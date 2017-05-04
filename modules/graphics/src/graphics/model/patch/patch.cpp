#include <graphics/model/patch/patch.h>

#include <graphics/shaders/program.h>

#include <GL/glew.h>

namespace ifx {

Patch::Patch(std::vector<Vertex> vertices,
             std::vector<GLuint> &indices,
             TesselationParams tesselation_params):
        Mesh(vertices, indices),
        tesselation_params_(tesselation_params) {
    primitive_draw_mode_ = PrimitiveDrawMode::PATCHES;
    polygon_mode_ = PolygonMode::FILL;
}

Patch::~Patch() {}

void Patch::bindTessLevel(const Program &program) {
    GLint tessInnerLoc
            = glGetUniformLocation(program.getID(),
                                   TESSELLATION_LVL_INNER_NAME.c_str());

    GLint tessOuterLoc
            = glGetUniformLocation(program.getID(),
                                   TESSELLATION_LVL_OUTER_NAME.c_str());

    GLint idILoc
            = glGetUniformLocation(program.getID(),
                                   PATCH_ID_I_NAME.c_str());
    GLint idJLoc
            = glGetUniformLocation(program.getID(),
                                   PATCH_ID_J_NAME.c_str());

    glUniform1f(tessInnerLoc, tesselation_params_.tess_level_inner);
    glUniform1f(tessOuterLoc, tesselation_params_.tess_level_outer);
    glUniform1i(idILoc, tesselation_params_.id_i);
    glUniform1i(idJLoc, tesselation_params_.id_j);

    glUniform1f(glGetUniformLocation(program.getID(),
                                     PATCH_ROW_COUNT_NAME.c_str()),
                tesselation_params_.row_count);
    glUniform1f(glGetUniformLocation(program.getID(),
                                     PATCH_COLUMN_COUNT_NAME.c_str()),
                tesselation_params_.column_count);
}

void Patch::draw(const Program &program) {
    bindTessLevel(program);

    glPatchParameteri(GL_PATCH_VERTICES,
                      tesselation_params_.vertex_count_per_patch);

    Mesh::draw(program);
}
}