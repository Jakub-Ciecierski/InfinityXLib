#ifndef DUCK_VBO_H
#define DUCK_VBO_H

#include <vector>
#include <graphics/shaders/data/shader_data.h>

typedef unsigned int GLenum;
typedef unsigned int GLuint;

enum class VBOUsage{
    Static, Dynamic
};

class VBO {
public:

    VBO(std::vector<Vertex> *vertices);
    ~VBO();

    std::vector<Vertex> *vertices() {return vertices_;}

    /*
     * Default usage is GL_STATIC_DRAW
     */
    void bind();

    void unbind();

    void Update();
private:
    GLenum GetNativeVBOUsage(VBOUsage usage);

    GLuint vboID;
    std::vector<Vertex> *vertices_;

    VBOUsage usage_;
};

#endif //DUCK_VBO_H
