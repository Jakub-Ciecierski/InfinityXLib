#ifndef PROJECT_TEXTURE_CREATOR_H
#define PROJECT_TEXTURE_CREATOR_H

#include <string>

#include <graphics/shaders/textures/texture.h>

namespace ifx {

class ResourceManager;

class TextureCreator {
public:

    TextureCreator(std::shared_ptr<ResourceManager> resource_manager);

    ~TextureCreator();

    std::shared_ptr<ResourceManager> resource_manager(){
        return resource_manager_;}

    std::shared_ptr<Texture2D> MakeTexture2DFromFile(
            std::string filepath, TextureTypes type);

    std::shared_ptr<Texture2D> MakeTexture2DEmpty(
            std::string filepath,
            TextureTypes type,
            TextureInternalFormat format,
            TexturePixelType pixel_type,
            int width, int height);
private:
    std::shared_ptr<ResourceManager> resource_manager_;
};

}

#endif //PROJECT_TEXTURE_CREATOR_H
