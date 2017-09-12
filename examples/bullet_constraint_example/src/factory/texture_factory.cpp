#include "factory/texture_factory.h"

#include <graphics/shaders/textures/texture_creator.h>

#include <resources/resource_manager.h>
#include <resources/resources.h>

namespace ifx {

using namespace std;

TextureFactory::TextureFactory(
    std::shared_ptr<TextureCreator> texture_creator) :
    texture_creator_(texture_creator) {}

TextureFactory::~TextureFactory() {}

std::shared_ptr<Texture2D> TextureFactory::CreateSolidColorTexture(
    const glm::vec3 &color,
    TextureTypes texture_type,
    int n, int m) {
    auto texture = texture_creator_->MakeTexture2DEmpty(NO_FILEPATH,
                                                        texture_type,
                                                        TextureInternalFormat::RGB,
                                                        TexturePixelType::UNSIGNED_BYTE,
                                                        n, m);
    int data_size = n * m * 3;
    std::vector<unsigned char> data;
    data.resize(data_size);
    int i = 0;
    while (i < data_size) {
        data[i++] = color.x;
        data[i++] = color.y;
        data[i++] = color.z;
    }
    texture->InitData((void *) data.data(), n, m);

    return texture;
}

std::shared_ptr<Texture2D> TextureFactory::LoadTesselationDiffuse() {
    auto resource_path = texture_creator_->resource_manager()->resource_path();

    return texture_creator_->MakeTexture2DFromFile(
        resource_path->GetResourcePath("teselation/diffuse.jpg",
                                       ifx::ResourceType::TEXTURE),
        TextureTypes::DIFFUSE);
}

std::shared_ptr<Texture2D> TextureFactory::LoadTesselationSpecular() {
    auto resource_path = texture_creator_->resource_manager()->resource_path();

    return texture_creator_->MakeTexture2DFromFile(
        resource_path->GetResourcePath("teselation/diffuse.jpg",
                                       ifx::ResourceType::TEXTURE),
        TextureTypes::SPECULAR);
}

std::shared_ptr<Texture2D> TextureFactory::LoadTesselationNormals() {
    auto resource_path = texture_creator_->resource_manager()->resource_path();

    return texture_creator_->MakeTexture2DFromFile(
        resource_path->GetResourcePath("teselation/normals.jpg",
                                       ifx::ResourceType::TEXTURE),
        TextureTypes::NORMAL);
}

std::shared_ptr<Texture2D> TextureFactory::LoadTesselationHeight() {
    auto resource_path = texture_creator_->resource_manager()->resource_path();

    return texture_creator_->MakeTexture2DFromFile(
        resource_path->GetResourcePath("teselation/height.jpg",
                                       ifx::ResourceType::TEXTURE),
        TextureTypes::DISPLACEMENT);
}

std::shared_ptr<Texture2D> TextureFactory::LoadContainerDiffuse() {
    auto resource_path = texture_creator_->resource_manager()->resource_path();

    return texture_creator_->MakeTexture2DFromFile(
        resource_path->GetResourcePath("container_diff.png",
                                       ifx::ResourceType::TEXTURE),
        TextureTypes::DIFFUSE);
}

std::shared_ptr<Texture2D> TextureFactory::LoadPortalTextureDiffuse() {
    auto resource_path = texture_creator_->resource_manager()->resource_path();

    return texture_creator_->MakeTexture2DFromFile(
        resource_path->GetResourcePath("portal/portal_wall.jpg",
                                       ifx::ResourceType::TEXTURE),
        TextureTypes::DIFFUSE);
}

std::shared_ptr<Texture2D> TextureFactory::LoadPortalTextureSpecular() {
    auto resource_path = texture_creator_->resource_manager()->resource_path();

    return texture_creator_->MakeTexture2DFromFile(
        resource_path->GetResourcePath("portal/portal_wall.jpg",
                                       ifx::ResourceType::TEXTURE),
        TextureTypes::SPECULAR);
}

std::shared_ptr<Texture2D> TextureFactory::LoadContainerSpecular() {
    auto resource_path = texture_creator_->resource_manager()->resource_path();

    return texture_creator_->MakeTexture2DFromFile(
        resource_path->GetResourcePath("container_specular.png",
                                       ifx::ResourceType::TEXTURE),
        TextureTypes::SPECULAR);
}

std::shared_ptr<Texture2D> TextureFactory::LoadAwesomeFace() {
    auto resource_path = texture_creator_->resource_manager()->resource_path();

    return texture_creator_->MakeTexture2DFromFile(
        resource_path->GetResourcePath("awesomeface.png",
                                       ifx::ResourceType::TEXTURE),
        TextureTypes::DIFFUSE);
}
}