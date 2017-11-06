#include "graphics/shaders/textures/texture_creator.h"

#include <resources/resource_manager.h>
#include <resources/resource_memory_cache.h>

#include <graphics/shaders/textures/texture.h>
#include <graphics/shaders/textures/texture_multisample.h>

#include <GL/glew.h>
#include <SOIL.h>

namespace ifx {

TextureCreator::TextureCreator(
    std::shared_ptr<ResourceManager> resource_manager) :
    resource_manager_(resource_manager) {}

std::shared_ptr<Texture2D> TextureCreator::MakeTexture2DFromFile(
    std::string filepath, TextureTypes type) {
    std::shared_ptr<Texture2D> texture
        = std::static_pointer_cast<Texture2D>(
            resource_manager_->resource_memory_cache()->Get(filepath));
    if (!texture) {
        TextureInternalFormat format = TextureInternalFormat::RGBA;
        TexturePixelType pixel_type = TexturePixelType::UNSIGNED_BYTE;
        texture = std::shared_ptr<Texture2D>(
            new Texture2D(filepath, type, format, pixel_type));
        texture->InitData((void *) nullptr, 0, 0);

        int width, height;
        int c = -1;
        unsigned char *image = SOIL_load_image(filepath.c_str(),
                                               &width, &height, &c,
                                               SOIL_LOAD_RGBA);
        if (image == NULL) {
            std::string info = "NULL returned";
            return nullptr;
        }
        //texture->InitData((void*)image, width, height);
        texture->Bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                     width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, image);
        texture->Unbind();
        SOIL_free_image_data(image);

        resource_manager_->resource_memory_cache()->Add(texture);
    }
    return texture;
}

std::shared_ptr<Texture2D> TextureCreator::MakeTexture2DEmpty(
    std::string filepath,
    TextureTypes type,
    TextureInternalFormat format,
    TexturePixelType pixel_type,
    int width, int height) {
    std::shared_ptr<Texture2D> texture
        = std::static_pointer_cast<Texture2D>(
            resource_manager_->resource_memory_cache()->Get(filepath));
    if (!texture) {
        texture = std::shared_ptr<Texture2D>(
            new Texture2D(filepath, type, format, pixel_type,
                          width, height));
        texture->InitData();
        resource_manager_->resource_memory_cache()->Add(texture);
    }
    return texture;
}

std::shared_ptr<Texture2D> TextureCreator::MakeTextureMultisample(
    TextureTypes type,
    TextureInternalFormat format,
    unsigned int sample_count,
    int width, int height) {
    auto texture = std::shared_ptr<TextureMultisample>(
        new TextureMultisample(type, format, sample_count, width, height));

    return texture;
}

}