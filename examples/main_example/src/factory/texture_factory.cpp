#include "factory/texture_factory.h"

#include <resources/resources.h>

namespace ifx {

using namespace std;

TextureFactory::TextureFactory() {

}

TextureFactory::~TextureFactory() {

}

std::shared_ptr<Texture2D> TextureFactory::CreateSolidColorTexture(
        const glm::vec3& color,
        TextureTypes texture_type,
        int n, int m){
    auto texture = Texture2D::MakeTexture2DEmpty(NO_FILEPATH,
                                                 texture_type,
                                                 TextureInternalFormat::RGB,
                                                 TexturePixelType::UNSIGNED_BYTE,
                                                 n, m);
    int data_size = n*m*3;
    std::vector<unsigned char> data;
    data.resize(data_size);
    int i = 0;
    while(i < data_size){
        data[i++] = color.x;
        data[i++] = color.y;
        data[i++] = color.z;
    }
    texture->InitData((void*)data.data(), n, m);

    return texture;
}

std::shared_ptr<Texture2D> TextureFactory::LoadTesselationDiffuse() {
    return Texture2D::MakeTexture2DFromFile(
            ifx::Resources::GetInstance()
                    .GetResourcePath("teselation/diffuse.jpg",
                                     ifx::ResourceType::TEXTURE),
            TextureTypes::DIFFUSE);
}

std::shared_ptr<Texture2D> TextureFactory::LoadTesselationSpecular() {
    return Texture2D::MakeTexture2DFromFile(
            ifx::Resources::GetInstance()
                    .GetResourcePath("teselation/diffuse.jpg",
                                     ifx::ResourceType::TEXTURE),
            TextureTypes::SPECULAR);
}

std::shared_ptr<Texture2D> TextureFactory::LoadTesselationNormals() {
    return Texture2D::MakeTexture2DFromFile(
            ifx::Resources::GetInstance()
                    .GetResourcePath("teselation/normals.jpg",
                                     ifx::ResourceType::TEXTURE),
            TextureTypes::NORMAL);
}

std::shared_ptr<Texture2D> TextureFactory::LoadTesselationHeight() {
    return Texture2D::MakeTexture2DFromFile(
            ifx::Resources::GetInstance()
                    .GetResourcePath("teselation/height.jpg",
                                     ifx::ResourceType::TEXTURE),
            TextureTypes::DISPLACEMENT);
}

std::shared_ptr<Texture2D> TextureFactory::LoadContainerDiffuse() {
    return Texture2D::MakeTexture2DFromFile(
            ifx::Resources::GetInstance()
                    .GetResourcePath("container_diff.png",
                                     ifx::ResourceType::TEXTURE),
            TextureTypes::DIFFUSE);
}

std::shared_ptr<Texture2D> TextureFactory::LoadPortalTextureDiffuse() {
    return Texture2D::MakeTexture2DFromFile(
            ifx::Resources::GetInstance()
                    .GetResourcePath("portal/portal_wall.jpg",
                                     ifx::ResourceType::TEXTURE),
            TextureTypes::DIFFUSE);
}

std::shared_ptr<Texture2D> TextureFactory::LoadPortalTextureSpecular() {
    return Texture2D::MakeTexture2DFromFile(
            ifx::Resources::GetInstance()
                    .GetResourcePath("portal/portal_wall.jpg",
                                     ifx::ResourceType::TEXTURE),
            TextureTypes::SPECULAR);
}

std::shared_ptr<Texture2D> TextureFactory::LoadContainerSpecular() {
    return Texture2D::MakeTexture2DFromFile(
            ifx::Resources::GetInstance()
                    .GetResourcePath("container_specular.png",
                                     ifx::ResourceType::TEXTURE),
            TextureTypes::SPECULAR);
}

std::shared_ptr<Texture2D> TextureFactory::LoadAwesomeFace() {
    return Texture2D::MakeTexture2DFromFile(
            ifx::Resources::GetInstance()
                    .GetResourcePath("awesomeface.png",
                                     ifx::ResourceType::TEXTURE),
            TextureTypes::DIFFUSE);
}
}