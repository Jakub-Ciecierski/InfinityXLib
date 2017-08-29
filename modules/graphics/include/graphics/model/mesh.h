#ifndef DUCK_MESH_H
#define DUCK_MESH_H

#include <graphics/model/material.h>
#include "graphics/shaders/program.h"
#include "graphics/shaders/data/shader_data.h"
#include "graphics/shaders/buffers/vbo.h"
#include "graphics/shaders/buffers/vao.h"

#include <memory>
#include <vector>

#include <iostream>

typedef unsigned int GLenum;

namespace ifx {

class Texture2D;

/**
 * Draw the polygon in filling mode or just the lines.
 */
enum class PolygonMode{
    FILL,
    LINES, // draw lines for Triangles
    LINE // Use for to draw lines for Patches
};

/**
 * How to interpret the vertices.
 */
enum class PrimitiveDrawMode{
    TRIANGLES, PATCHES,
    LINES, POINTS
};

/*
 * Contains the geometry of an object.
 * Vertices, indices, textures and material is defined.
 *
 * One instance of the same Mesh should be present in the system.
 * Use Multiple RenderObjects to bind the same Mesh
 */
class Mesh {
public:
    Mesh(std::vector<Vertex> vertices,
         std::vector<GLuint> &indices);

    Mesh(const Mesh &mesh) = delete;
    Mesh &operator=(const Mesh &other) = delete;

    virtual ~Mesh() = default;

    const std::vector<Vertex> &vertices() { return vertices_; }
    const std::vector<unsigned int>& indices() {return indices_;}

    VAO *vao() { return vao_.get(); };
    VBO *vbo() { return vbo_.get(); };

    std::shared_ptr<Material> material(){return material_;}
    void material(std::shared_ptr<Material> material){material_ = material;}

    PrimitiveDrawMode primitive_draw_mode(){return primitive_draw_mode_;}
    PolygonMode polygon_mode() {return polygon_mode_;}
    void primitive_draw_mode(PrimitiveDrawMode mode){
        primitive_draw_mode_ = mode;}
    void polygon_mode(PolygonMode mode) {polygon_mode_ = mode;}

    virtual void draw(const Program &program);
    virtual void drawInstanced(const Program &program, int count);

    std::string toString() const;

protected:
    void initBuffers();

    /*
     * Binds all textures during draw operation
     */
    void bindTextures(const Program &program);
    void BindTexture(std::shared_ptr<Texture2D> texture,
                     std::string program_location,
                     const Program &program, int id);
    void unbindTextures();

    void bindColor(const Program &program);

    GLenum PrimitiveDrawModeToNative(PrimitiveDrawMode mode);
    GLenum PolygonModeToNative(PolygonMode mode);

    std::vector<Vertex> vertices_;
    std::vector<GLuint> indices_;
    std::shared_ptr<Material> material_;

    PrimitiveDrawMode primitive_draw_mode_;
    PolygonMode polygon_mode_;

    std::unique_ptr<VAO> vao_;
    std::unique_ptr<VBO> vbo_;
    std::unique_ptr<EBO> ebo_;
};
}

#endif //DUCK_MESH_H
