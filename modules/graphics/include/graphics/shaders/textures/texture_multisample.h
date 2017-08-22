#ifndef PROJECT_TEXTURE_MULTISAMPLE_H
#define PROJECT_TEXTURE_MULTISAMPLE_H

#include "graphics/shaders/textures/texture.h"

namespace ifx {

class TextureMultisample : public Texture2D {
public:
    ~TextureMultisample() = default;

    virtual void InitData(void* data, int width, int height) override;

    friend class TextureCreator;
private:
    TextureMultisample(
            TextureTypes type,
            TextureInternalFormat internal_format,
            unsigned int sample_count,
            float width, float height);

    unsigned int sample_count_;
};
}

#endif //PROJECT_TEXTURE_MULTISAMPLE_H
