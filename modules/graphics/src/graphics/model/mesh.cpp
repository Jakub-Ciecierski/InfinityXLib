#include <sstream>

#include <graphics/shaders/textures/texture_activator.h>
#include "graphics/model/mesh.h"
#include <graphics/model/material.h>

#include <common/unique_ptr.h>

#include <GL/glew.h>

using namespace std;

namespace ifx {

Mesh::Mesh(std::vector<Vertex> vertices,
           vector<GLuint> &indices) :
    vertices_(vertices),
    indices_(indices),
    material_(std::make_shared<Material>()),
    primitive_draw_mode_(PrimitiveDrawMode::TRIANGLES),
    polygon_mode_(PolygonMode::FILL) {
    initBuffers();
}

void Mesh::initBuffers() {
    vao_ = ifx::make_unique<VAO>();
    vbo_ = ifx::make_unique<VBO>(&vertices_);
    ebo_ = ifx::make_unique<EBO>(&indices_);

    vao_->bindVertexBuffers(*vbo_, *ebo_);
}

void Mesh::bindTextures(const Program &program) {
    BindTexture(material_->diffuse, MATERIAL_DIFFUSE_NAME, program, 0);
    BindTexture(material_->specular, MATERIAL_SPECULAR_NAME, program, 1);
    BindTexture(material_->normal, MATERIAL_NORMAL_NAME, program, 2);
    BindTexture(material_->displacement,
                MATERIAL_DISPLACEMENT_NAME,
                program,
                3);
    BindTexture(material_->fbo, TEXTURE_SCREEN_NAME, program, 4);
}

void Mesh::BindTexture(std::shared_ptr<Texture2D> texture,
                       std::string program_location,
                       const Program &program, int id) {
    if (!texture) {
        return;
    }

    int i = TextureActivator::GetInstance().GetNextLocalID();
    glActiveTexture(GL_TEXTURE0 + i);
    texture->Bind();
    glUniform1i(glGetUniformLocation(program.getID(),
                                     program_location.c_str()), i);
}

void Mesh::unbindTextures() {
    if (material_->diffuse)
        material_->diffuse->Unbind();
    if (material_->specular)
        material_->specular->Unbind();
    if (material_->normal)
        material_->normal->Unbind();
    if (material_->displacement)
        material_->displacement->Unbind();
    if (material_->fbo)
        material_->fbo->Unbind();
}

void Mesh::bindColor(const Program &program) {
    GLint matShineLoc = glGetUniformLocation(program.getID(),
                                             MATERIAL_SHININESS_NAME.c_str());
    glUniform1f(matShineLoc, material_->shininess);

    GLint alphaLoc = glGetUniformLocation(program.getID(),
                                          MATERIAL_ALPHA_NAME.c_str());
    glUniform1f(alphaLoc, material_->alpha);
}

void Mesh::draw(const Program &program) {
    TextureActivator::GetInstance().ResetLocal();
    program.use();

    glPolygonMode(GL_FRONT_AND_BACK,
                  PolygonModeToNative(polygon_mode_));

    this->bindTextures(program);
    this->bindColor(program);

    vao_->bind();

    glDrawElements(PrimitiveDrawModeToNative(primitive_draw_mode_),
                   indices_.size(), GL_UNSIGNED_INT, 0);

    vao_->unbind();
    this->unbindTextures();
}

void Mesh::drawInstanced(const Program &program, int count) {
    program.use();

    glPolygonMode(GL_FRONT_AND_BACK,
                  PolygonModeToNative(polygon_mode_));

    this->bindTextures(program);
    this->bindColor(program);

    vao_->bind();

    glDrawElementsInstanced(PrimitiveDrawModeToNative(primitive_draw_mode_),
                            indices_.size(),
                            GL_UNSIGNED_INT, 0, count);

    vao_->unbind();
}

std::string Mesh::toString() const {
    std::stringstream ss;
    std::string header_space = "   ";
    std::string inner_header_space = "      ";
    ss << header_space << "Material: " << std::endl;

    if (material_->diffuse)
        ss << inner_header_space << "Diffuse" << std::endl;
    if (material_->specular)
        ss << inner_header_space << "Specular" << std::endl;
    if (material_->normal)
        ss << inner_header_space << "Normal" << std::endl;
    if (material_->displacement)
        ss << inner_header_space << "Displacement" << std::endl;
    return ss.str();
}

GLenum Mesh::PrimitiveDrawModeToNative(PrimitiveDrawMode mode) {
    if (mode == PrimitiveDrawMode::TRIANGLES)
        return GL_TRIANGLES;
    else if (mode == PrimitiveDrawMode::PATCHES)
        return GL_PATCHES;
    else if (mode == PrimitiveDrawMode::LINES)
        return GL_LINES;
    else if (mode == PrimitiveDrawMode::POINTS)
        return GL_POINTS;
    else
        return GL_ERROR_REGAL;
}

GLenum Mesh::PolygonModeToNative(PolygonMode mode) {
    if (mode == PolygonMode::FILL)
        return GL_FILL;
    else if (mode == PolygonMode::LINES)
        return GL_LINES;
    else if (mode == PolygonMode::LINE)
        return GL_LINE;
    else
        return GL_ERROR_REGAL;
}

}