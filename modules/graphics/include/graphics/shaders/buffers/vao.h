#ifndef DUCK_VAO_H
#define DUCK_VAO_H

#include "graphics/shaders/buffers/vbo.h"
#include "graphics/shaders/buffers/ebo.h"

typedef unsigned int GLuint;

class VAO {
public:

    VAO();

    ~VAO();

    void bindVertexBuffers(VBO &vbo, EBO &ebo);
    void bindInstancedRenderingBuffers(InstancedData &instanced_data);

    void bind();
    void unbind();

private:
    GLuint id;
};

#endif //DUCK_VAO_H
