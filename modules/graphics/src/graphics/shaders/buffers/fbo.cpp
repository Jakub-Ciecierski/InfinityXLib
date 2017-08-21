#include "graphics/shaders/buffers/fbo.h"

#include <graphics/shaders/textures/texture.h>

#include <GL/glew.h>

namespace ifx {

FBO::FBO(std::shared_ptr<Texture2D> texture, const FBOType& type) :
        type_(type),
        texture_(texture),
        compiled_(false){
    glGenFramebuffers(1, &id_);
}

FBO::~FBO() {
    glDeleteFramebuffers(1, &id_);
}

void FBO::compile(){
    if(compiled_)
        return;

    bind();

    if(type_.buffer == FBOBuffer::COLOR_DEPTH)
        compileColorDepth();
    else if(type_.buffer == FBOBuffer::DEPTH)
        compileDepth();

    CheckError();
    unbind();

    compiled_ = true;
}

void FBO::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, id_);
}

void FBO::unbind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::compileColorDepth(){
    compileTexture(GL_COLOR_ATTACHMENT0);
    compileRBO();
}

void FBO::compileDepth(){
    compileTexture(GL_DEPTH_ATTACHMENT);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
}

void FBO::compileTexture(GLenum attachment){
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           attachment,
                           GL_TEXTURE_2D, texture_->id(), 0);
}

void FBO::compileRBO(){
    auto multiplier = GetMultiplier(type_.anti_aliasing_multiplier);
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,
                          texture_->width() * multiplier,
                          texture_->height() * multiplier);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, rbo);
}

void FBO::CheckError(){
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw new std::invalid_argument("Framebuffer is not complete!");
}

unsigned int FBO::GetMultiplier(FBOAAColorBufferMultiplier& aa){
    switch(aa){
        case FBOAAColorBufferMultiplier::NONE:
            return 1;
        case FBOAAColorBufferMultiplier::AA2:
            return 21;
        case FBOAAColorBufferMultiplier::AA4:
            return 4;
        case FBOAAColorBufferMultiplier::AA8:
            return 8;
        case FBOAAColorBufferMultiplier::AA16:
            return 16;
    }
}

} // ifx