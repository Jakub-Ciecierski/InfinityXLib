#ifndef PROJECT_TEXTURE_H
#define PROJECT_TEXTURE_H

#include <resources/resource.h>
#include <GL/glew.h>

#include <memory>

namespace ifx {

enum class TextureTypes{
    DIFFUSE, SPECULAR, NORMAL, DISPLACEMENT, CUBEMAP, FBO
};

enum class TextureInternalFormat{
    R, RGB, DEPTH_COMPONENT
};

enum class TexturePixelType{
    FLOAT, UNSIGNED_BYTE
};

struct TextureParameter{
    GLenum param;
    GLenum value;
};

class Texture2D : public Resource{
public:
    ~Texture2D();
    static std::shared_ptr<Texture2D> MakeTexture2DFromFile(
            std::string filepath, TextureTypes type);
    static std::shared_ptr<Texture2D> MakeTexture2DEmpty(
            std::string filepath,
            TextureTypes type,
            TextureInternalFormat format,
            TexturePixelType pixel_type,
            int width = 0, int height = 0);

    GLuint id(){return id_;}
    TextureTypes texture_type(){return type_;}
    TextureInternalFormat format(){return format_;}
    TexturePixelType pixel_type(){return pixel_type_;}
    int width(){return width_;}
    int height(){return height_;}

    void AddParameter(TextureParameter param);
    void InitData(void* data, int width, int height);

    void Bind();
    void Unbind();
private:
    Texture2D(std::string filepath,
              TextureTypes type,
              TextureInternalFormat format,
              TexturePixelType pixel_type,
              int width = 0, int height = 0);

    GLenum GetTextureInternalFormatPrimitive();
    GLenum GetTexturePixelTypePrimitive();

    GLuint id_;
    TextureTypes type_;
    TextureInternalFormat format_;
    TexturePixelType pixel_type_;
    int width_;
    int height_;
};
}

#endif //PROJECT_TEXTURE_H
