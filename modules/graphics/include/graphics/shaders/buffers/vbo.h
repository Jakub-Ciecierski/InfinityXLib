#ifndef DUCK_VBO_H
#define DUCK_VBO_H

#include <vector>
#include <graphics/shaders/data/shader_data.h>

typedef unsigned int GLenum;
typedef unsigned int GLuint;

class VBO {
private:
    GLuint vboID;
    const std::vector<Vertex> *vertices;

public:

    VBO(const std::vector<Vertex> *vertices);
    ~VBO();

    /*
     * Default usage is GL_STATIC_DRAW
     */
    void bind(GLenum usage);

    void unbind();
};

#endif //DUCK_VBO_H
