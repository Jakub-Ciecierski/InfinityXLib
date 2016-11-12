#ifndef PROJECT_FBO_H
#define PROJECT_FBO_H

#include <GL/glew.h>
#include <shaders/data/shader_data.h>

#include <memory>

namespace ifx {

class Texture2D;

/**
 * Determines the type of FBO.
 * What buffers to bind.
 */
enum class FBOType{
    COLOR_DEPTH, DEPTH, COLOR
};

/**
 * Frame Buffer Object. Created RenderObjectBuffer for depth and stencil.
 * Must call compile before using.
 */
class FBO {
public:

    FBO(std::shared_ptr<Texture2D> texture, FBOType type);

    ~FBO();

    std::shared_ptr<Texture2D> texture(){return texture_;}

    /**
     * Finishes the creation of FBO.
     * Binds the texture and completes FBO.
     * Throws exception if FBO compilation not was not complete.
     */
    void compile();

    /**
     * Binds to this FBO
     */
    void bind();

    /**
     * Unbinds from this FBO and binds back to default FBO.
     */
    void unbind();

private:

    /**
     * Compile based on the type
     */
    void compileColorDepth();
    void compileDepth();

    void compileTexture(GLenum attachment);
    void compileRBO();

    void CheckError();

    FBOType type_;

    GLuint id_;
    std::shared_ptr<Texture2D> texture_;

    bool compiled_;
};

}

#endif //PROJECT_FBO_H
