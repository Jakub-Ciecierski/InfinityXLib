#ifndef TESELATION_PATCH_H
#define TESELATION_PATCH_H

#include <graphics/model/mesh.h>

namespace ifx {

struct TesselationParams {
    float tess_level_inner;
    float tess_level_outer;
    long unsigned int vertex_count_per_patch;
    int id_i;
    int id_j;
    int row_count;
    int column_count;
};

/*
 * Patch DrawingMode is always set to GL_PATCHES
 */
class Patch : public Mesh {
public:
    Patch(std::vector<Vertex> vertices,
          std::vector<GLuint> &indices,
          TesselationParams tesselation_params);

    ~Patch();

    virtual void draw(const Program &program) override;
private:
    void bindTessLevel(const Program &program);
    void drawPolygon();

    TesselationParams tesselation_params_;
};
}

#endif //TESELATION_PATCH_H
