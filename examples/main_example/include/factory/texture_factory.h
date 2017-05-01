#ifndef PROJECT_TEXTURE_FACTORY_H
#define PROJECT_TEXTURE_FACTORY_H

#include "graphics/shaders/data/shader_data.h"
#include <graphics/shaders/textures/texture.h>

#include <memory>

namespace ifx {

class TextureFactory {
private:

public:

    TextureFactory();

    ~TextureFactory();

    std::shared_ptr<Texture2D> CreateSolidColorTexture(
            const glm::vec3& color,
            TextureTypes texture_type,
            int n = 1, int m = 1);

    std::shared_ptr<Texture2D> LoadExampleCubemap();

    std::shared_ptr<Texture2D> LoadDynamicBlueDiffuseTexture();

    std::shared_ptr<Texture2D> LoadDynamicBlueSpecularTexture();

    std::shared_ptr<Texture2D> LoadTesselationDiffuse();

    std::shared_ptr<Texture2D> LoadTesselationSpecular();

    std::shared_ptr<Texture2D> LoadTesselationNormals();

    std::shared_ptr<Texture2D> LoadTesselationHeight();

    std::shared_ptr<Texture2D> LoadContainer();
    std::shared_ptr<Texture2D> LoadPortalTextureDiffuse();
    std::shared_ptr<Texture2D> LoadPortalTextureSpecular();
    std::shared_ptr<Texture2D> LoadContainerDiffuse();

    std::shared_ptr<Texture2D> LoadContainerSpecular();

    std::shared_ptr<Texture2D> LoadAwesomeFace();

};
} // ifx

#endif //PROJECT_TEXTURE_FACTORY_H
