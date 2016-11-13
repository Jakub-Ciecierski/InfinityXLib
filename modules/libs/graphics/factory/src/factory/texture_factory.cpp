#include "factory/texture_factory.h"

#include <resources/resources.h>

namespace ifx {

using namespace std;

TextureFactory::TextureFactory() {

}

TextureFactory::~TextureFactory() {

}
/*
std::shared_ptr<Texture2D> TextureFactory::LoadExampleCubemap() {
    TextureLoader textureLoader;

    ifx::Resources &resources = ifx::Resources::GetInstance();
    string filepathBase = resources.GetResourcePath("cubemap/sor_sea/sea_",
                                                    ifx::ResourceType::TEXTURE);
    std::vector<std::string> filepathFaces = {
            filepathBase + "rt.JPG",
            filepathBase + "lf.JPG",
            filepathBase + "up.JPG",
            filepathBase + "dn.JPG",
            filepathBase + "bk.JPG",
            filepathBase + "ft.JPG"
    };
    return textureLoader.loadCubemap(filepathFaces);
}
*/
/*
std::shared_ptr<Texture2D> TextureFactory::LoadDynamicBlueDiffuseTexture() {
    TextureLoader textureLoader;

    int width = 15;
    int height = 15;
    int pixel_data = 1;
    int count = width * height * pixel_data;
    int pixelCount = count / pixel_data;
    float *data = new float[count];

    int pixelIndex = 0;
    for (int i = 0; i < pixelCount; i++) {
        data[pixelIndex] = (float)i/(float)pixelCount;

        pixelIndex += pixel_data;
    }
    Texture texture = textureLoader.loadFromDataRED(TextureTypes::DIFFUSE, data,
                                                 width, height);

    delete data;

    return texture;
}*/
/*
Texture TextureFactory::LoadDynamicBlueDiffuseTexture() {
    TextureLoader textureLoader;

    int width = 128;
    int height = 128;
    int pixel_data = 3;
    int count = width * height * pixel_data;
    int pixelCount = count / pixel_data;
    unsigned char *data = new unsigned char[count];

    int pixelIndex = 0;
    for (int i = 0; i < pixelCount; i++) {
        data[pixelIndex + 0] = 0;
        data[pixelIndex + 1] = 125;
        data[pixelIndex + 2] = 0;

        pixelIndex += pixel_data;
    }
    Texture texture = textureLoader.loadFromData(TextureTypes::DIFFUSE, data,
                                                 width, height);

    delete data;

    return texture;
}*/
/*
std::shared_ptr<Texture2D> TextureFactory::LoadDynamicBlueSpecularTexture() {
    TextureLoader textureLoader;

    int width = 128;
    int height = 128;
    int pixel_data = 3;
    int count = width * height * pixel_data;
    int pixelCount = (count) / pixel_data;
    unsigned char *data = new unsigned char[count];

    int pixelIndex = 0;
    for (int i = 0; i < pixelCount; i++) {
        data[pixelIndex + 0] = 0;
        data[pixelIndex + 1] = 255;
        data[pixelIndex + 2] = 0;

        pixelIndex += pixel_data;
    }
    Texture texture = textureLoader.loadFromData(TextureTypes::SPECULAR,
                                                 data, width, height);

    delete data;

    return texture;
}
*/
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