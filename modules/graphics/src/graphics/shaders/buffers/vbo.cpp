#include <GL/glew.h>

#include "graphics/shaders/data/shader_data.h"
#include "graphics/shaders/buffers/vbo.h"

#include <iostream>

using namespace std;

VBO::VBO(std::vector<Vertex> *vertices) :
    vertices_(vertices),
    usage_(VBOUsage::Static){
    glGenBuffers(1, &vboID);
}

VBO::~VBO() {
    glDeleteBuffers(1, &vboID);
}

void VBO::Update(){
    GLuint bytesCount = sizeof(Vertex) * vertices_->size();
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    bytesCount,
                    vertices_->data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::bind() {
    GLuint bytesCount = sizeof(Vertex) * vertices_->size();

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER,
                 bytesCount,
                 vertices_->data(),
                 GetNativeVBOUsage(usage_));
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLenum VBO::GetNativeVBOUsage(VBOUsage usage){
    switch(usage){
        case VBOUsage::Static:
            return GL_STATIC_DRAW;
        case VBOUsage::Dynamic:
            return GL_DYNAMIC_DRAW;
    }
    return GL_STATIC_DRAW;
}
