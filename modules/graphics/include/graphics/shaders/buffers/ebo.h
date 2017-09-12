#ifndef DUCK_EBO_H
#define DUCK_EBO_H

#include <vector>

typedef unsigned int GLuint;
typedef unsigned int GLenum;

class EBO {
private:
    GLuint id;
    const std::vector<GLuint> *indices;

public:

    EBO(const std::vector<GLuint> *indices);

    ~EBO();

    void bind(GLenum usage);
    void unbind();
};

#endif //DUCK_EBO_H
