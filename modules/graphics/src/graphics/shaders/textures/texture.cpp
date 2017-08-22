#include "graphics/shaders/textures/texture.h"

#include <resources/resource_memory_cache.h>

#include <GL/glew.h>

#include <SOIL.h>

namespace ifx{

// private
Texture2D::Texture2D(std::string filepath,
                     TextureTypes type,
                     TextureInternalFormat format,
                     TexturePixelType pixel_type,
                     int width, int height) :
        Resource(filepath, ResourceType::TEXTURE),
        type_(type),
        format_(format),
        pixel_type_(pixel_type),
        target_(TextureTarget::Normal),
        width_(width), height_(height){
    glGenTextures(1, &id_);
}

Texture2D::~Texture2D(){
    glDeleteTextures(1, &id_);
}

void Texture2D::AddParameter(TextureParameter param){
    Bind();
    glTexParameteri(GetTextureTargetPrimitive(), param.param, param.value);
    Unbind();
}

void Texture2D::InitData(){
    InitData(nullptr, width_, height_);
}

void Texture2D::InitData(int width, int height){
    InitData(nullptr, width, height);
}

void Texture2D::InitData(void* data, int width, int height){
    Bind();
    width_ = width;
    height_ = height;

    if(pixel_type_ == TexturePixelType::UNSIGNED_BYTE){
        glTexImage2D(GL_TEXTURE_2D, 0, GetTextureInternalFormatPrimitive(),
                     width, height, 0, GetTextureInternalFormatPrimitive(),
                     GetTexturePixelTypePrimitive(), (unsigned char*)data);
    }else if(pixel_type_ == TexturePixelType::FLOAT){
        glTexImage2D(GL_TEXTURE_2D, 0, GetTextureInternalFormatPrimitive(),
                     width, height, 0, GetTextureInternalFormatPrimitive(),
                     GetTexturePixelTypePrimitive(), (float*)data);
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    Unbind();

    AddParameter(TextureParameter{GL_TEXTURE_WRAP_S, GL_REPEAT});
    AddParameter(TextureParameter{GL_TEXTURE_WRAP_T, GL_REPEAT});

    AddParameter(TextureParameter{GL_TEXTURE_MIN_FILTER, GL_LINEAR});
    AddParameter(TextureParameter{GL_TEXTURE_MAG_FILTER, GL_LINEAR});
}

void Texture2D::Bind(){
    glBindTexture(GetTextureTargetPrimitive(), id_);
}
void Texture2D::Unbind(){
    glBindTexture(GetTextureTargetPrimitive(), 0);
}

GLenum Texture2D::GetTextureInternalFormatPrimitive(){
    if(format_ == TextureInternalFormat::R)
        return GL_RED;
    else if(format_ == TextureInternalFormat::RGB)
        return GL_RGB;
    else if(format_ == TextureInternalFormat::RGBA)
        return GL_RGBA;
    else if(format_ == TextureInternalFormat::DEPTH_COMPONENT)
        return GL_DEPTH_COMPONENT;
    else
        return GL_ERROR_REGAL;
}

GLenum Texture2D::GetTexturePixelTypePrimitive(){
    if(pixel_type_ == TexturePixelType::FLOAT)
        return GL_FLOAT;
    else if(pixel_type_ == TexturePixelType::UNSIGNED_BYTE)
        return GL_UNSIGNED_BYTE;
    else
        return GL_ERROR_REGAL;
}

GLenum Texture2D::GetTextureTargetPrimitive(){
    switch(target_){
        case TextureTarget::Normal:
            return GL_TEXTURE_2D;
        case TextureTarget::MultiSample:
            return GL_TEXTURE_2D_MULTISAMPLE;
    }
    return GL_TEXTURE_2D;
}

}