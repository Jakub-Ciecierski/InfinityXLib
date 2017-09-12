#ifndef PROJECT_TEXTURE_H
#define PROJECT_TEXTURE_H

#include <resources/resource.h>

#include <memory>

typedef unsigned int GLenum;
typedef unsigned int GLuint;

namespace ifx {

class TextureCreator;

enum class TextureTypes {
    DIFFUSE, SPECULAR, NORMAL, DISPLACEMENT, CUBEMAP, FBO
};

enum class TextureInternalFormat {
    R, RGB, RGBA, DEPTH_COMPONENT
};

enum class TexturePixelType {
    FLOAT, UNSIGNED_BYTE
};

enum class TextureTarget {
    Normal, MultiSample
};

struct TextureParameter {
    GLenum param;
    GLenum value;
};

class Texture2D : public Resource {
public:
    virtual ~Texture2D();

    GLuint id() const { return id_; }
    TextureTypes texture_type() { return type_; }
    TextureInternalFormat format() { return format_; }
    TexturePixelType pixel_type() { return pixel_type_; }
    int width() const { return width_; }
    int height() const { return height_; }

    void AddParameter(TextureParameter param);

    virtual void InitData();
    virtual void InitData(int width, int height);
    virtual void InitData(void *data, int width, int height);

    void Bind();
    void Unbind();

    GLenum GetTextureInternalFormatPrimitive();
    GLenum GetTexturePixelTypePrimitive();
    GLenum GetTextureTargetPrimitive();

    friend class TextureCreator;

protected:
    Texture2D(std::string filepath,
              TextureTypes type,
              TextureInternalFormat format,
              TexturePixelType pixel_type,
              int width = 0, int height = 0);

    GLuint id_;
    TextureTypes type_;
    TextureInternalFormat format_;
    TexturePixelType pixel_type_;
    TextureTarget target_;

    int width_;
    int height_;

};
}

#endif //PROJECT_TEXTURE_H
