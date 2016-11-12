#include "shaders/textures/texture.h"

#include <resources/resource_memory_cache.h>

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
        width_(width), height_(height){
    glGenTextures(1, &id_);
    InitData(nullptr, width_, height_);

    AddParameter(TextureParameter{GL_TEXTURE_WRAP_S, GL_REPEAT});
    AddParameter(TextureParameter{GL_TEXTURE_WRAP_T, GL_REPEAT});

    AddParameter(TextureParameter{GL_TEXTURE_MIN_FILTER, GL_LINEAR});
    AddParameter(TextureParameter{GL_TEXTURE_MAG_FILTER, GL_LINEAR});
}

Texture2D::~Texture2D(){
    glDeleteTextures(1, &id_);
}

// static
std::shared_ptr<Texture2D> Texture2D::MakeTexture2DFromFile(
        std::string filepath, TextureTypes type){
    std::shared_ptr<Texture2D> texture
            = std::static_pointer_cast<Texture2D>(
                    ifx::ResourceMemoryCache::GetInstance().Get(filepath));
    if(!texture) {
        TextureInternalFormat format = TextureInternalFormat::RGB;
        TexturePixelType pixel_type = TexturePixelType::UNSIGNED_BYTE;
        texture = std::shared_ptr<Texture2D>(
                new Texture2D(filepath, type, format, pixel_type));
        int width, height;
        unsigned char *image = SOIL_load_image(filepath.c_str(),
                                               &width, &height, 0,
                                               SOIL_LOAD_RGB);
        if (image == NULL) {
            std::string info = "NULL returned";
            throw new std::invalid_argument(info);
        }
        //texture->InitData((void*)image, width, height);
        texture->Bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, image);
        texture->Unbind();
        SOIL_free_image_data(image);

        ifx::ResourceMemoryCache::GetInstance().Add(texture);
    }
    return texture;
}

// static
std::shared_ptr<Texture2D> Texture2D::MakeTexture2DEmpty(
        std::string filepath,
        TextureTypes type,
        TextureInternalFormat format,
        TexturePixelType pixel_type,
        int width, int height){
    std::shared_ptr<Texture2D> texture
            = std::static_pointer_cast<Texture2D>(
                    ifx::ResourceMemoryCache::GetInstance().Get(filepath));
    if(!texture) {
        texture = std::shared_ptr<Texture2D>(
                new Texture2D(filepath, type, format, pixel_type,
                width, height));

        ifx::ResourceMemoryCache::GetInstance().Add(texture);
    }
    return texture;
}

void Texture2D::AddParameter(TextureParameter param){
    Bind();
    glTexParameteri(GL_TEXTURE_2D, param.param, param.value);
    Unbind();
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
}

void Texture2D::Bind(){
    glBindTexture(GL_TEXTURE_2D, id_);
}
void Texture2D::Unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLenum Texture2D::GetTextureInternalFormatPrimitive(){
    if(format_ == TextureInternalFormat::R)
        return GL_RED;
    if(format_ == TextureInternalFormat::RGB)
        return GL_RGB;
    else if(format_ == TextureInternalFormat::DEPTH_COMPONENT)
        return GL_DEPTH_COMPONENT;
}
GLenum Texture2D::GetTexturePixelTypePrimitive(){
    if(pixel_type_ == TexturePixelType::FLOAT)
        return GL_FLOAT;
    else if(pixel_type_ == TexturePixelType::UNSIGNED_BYTE)
        return GL_UNSIGNED_BYTE;
}

}