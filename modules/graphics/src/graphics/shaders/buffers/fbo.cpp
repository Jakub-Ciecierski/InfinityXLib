#include "graphics/shaders/buffers/fbo.h"

#include <graphics/shaders/textures/texture.h>

#include <GL/glew.h>
#include <iostream>

namespace ifx {

FBO::FBO(std::shared_ptr<Texture2D> texture, const FBOType& type) :
        type_(type),
        texture_(texture),
        compiled_(false){
    CreateFBO();
}

FBO::~FBO() {
    DeleteFBO();
}

void FBO::Compile(){
    if(compiled_){
        DeleteFBO();
        CreateFBO();
    }

    Bind();

    switch(type_.buffer){
        case FBOBuffer::COLOR_DEPTH:
            CompileColorDepth();
            break;
        case FBOBuffer::DEPTH:
            CompileDepth();
            break;
        case FBOBuffer::COLOR:
            CompileColor();
            break;
    }
    CheckError();

    Unbind();

    compiled_ = true;
}

void FBO::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, id_);
}

void FBO::Unbind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::CreateFBO(){
    glGenFramebuffers(1, &id_);
}

void FBO::DeleteFBO(){
    glDeleteFramebuffers(1, &id_);
}

void FBO::CompileColorDepth(){
    CompileColor();
    CompileRBO();
}

void FBO::CompileDepth(){
    CompileTexture(GL_DEPTH_ATTACHMENT);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
}

void FBO::CompileColor(){
    CompileTexture(GL_COLOR_ATTACHMENT0);
}

void FBO::CompileTexture(GLenum attachment){
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           attachment,
                           texture_->GetTextureTargetPrimitive(),
                           texture_->id(),
                           0);
}

void FBO::CompileRBO(){
    auto multiplier = GetMultiplier(type_.msaa);
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);

    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    if(multiplier != 0){
        glRenderbufferStorageMultisample(GL_RENDERBUFFER,
                                         multiplier,
                                         GL_DEPTH24_STENCIL8,
                                         texture_->width(),
                                         texture_->height());
    }else{
        glRenderbufferStorage(GL_RENDERBUFFER,
                              GL_DEPTH24_STENCIL8,
                              texture_->width(),
                              texture_->height());
    }
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, rbo);
}

void FBO::CheckError(){
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;

        throw std::invalid_argument("Framebuffer is not complete!" +
                                    glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }
}

unsigned int FBO::GetMultiplier(FBO_MSAA& aa){
    switch(aa){
        case FBO_MSAA::NONE:
            return 1;
        case FBO_MSAA::AA2:
            return 2;
        case FBO_MSAA::AA4:
            return 4;
        case FBO_MSAA::AA8:
            return 8;
        case FBO_MSAA::AA16:
            return 16;
    }
    return 0;
}

} // ifx