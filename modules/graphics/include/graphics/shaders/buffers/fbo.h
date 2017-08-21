#ifndef PROJECT_FBO_H
#define PROJECT_FBO_H

#include <graphics/shaders/data/shader_data.h>

#include <memory>

typedef unsigned int GLenum;
typedef unsigned int GLuint;

namespace ifx {

class Texture2D;

/**
 * Determines the type of FBO.
 * What buffers to bind.
 */
enum class FBOBuffer {
    COLOR_DEPTH, DEPTH, COLOR
};

/**
 * Anti-Aliasing. Increase Color Buffer by AAx
 */
enum class FBOAAColorBufferMultiplier{
    NONE, AA2, AA4, AA8, AA16
};

struct FBOType{
    FBOBuffer buffer;
    FBOAAColorBufferMultiplier anti_aliasing_multiplier;
};

/**
 * Frame Buffer Object. Created RenderObjectBuffer for depth and stencil.
 * Must call compile before using.
 */
class FBO {
public:

    FBO(std::shared_ptr<Texture2D> texture, const FBOType& type);

    ~FBO();

    std::shared_ptr<Texture2D> texture() const {return texture_;}

    /**
     * Finishes the creation of FBO.
     * Binds the texture and completes FBO.
     * Throws exception if FBO compilation not was not complete.
     */
    void Compile();

    /**
     * Binds to this FBO
     */
    void Bind();

    /**
     * Unbinds from this FBO and binds back to default FBO.
     */
    void Unbind();

private:
    void CreateFBO();
    void DeleteFBO();

    /**
     * Compile based on the type
     */
    void CompileColorDepth();
    void CompileDepth();

    void CompileTexture(GLenum attachment);
    void CompileRBO();

    void CheckError();

    unsigned int GetMultiplier(FBOAAColorBufferMultiplier& aa);

    FBOType type_;

    GLuint id_;
    std::shared_ptr<Texture2D> texture_;

    bool compiled_;
};

}

#endif //PROJECT_FBO_H
