#include "graphics/shaders/textures/texture_multisample.h"

#include <GL/glew.h>

namespace ifx{

TextureMultisample::TextureMultisample(
        TextureTypes type,
        TextureInternalFormat internal_format,
        unsigned int sample_count,
        float width, float height) :
        Texture2D(ifx::NO_FILEPATH, type, internal_format,
                  TexturePixelType::UNSIGNED_BYTE, width, height),
        sample_count_(sample_count){
    target_ = TextureTarget::MultiSample;
}

void TextureMultisample::InitData(void* data, int width, int height){
    Bind();
    width_ = width;
    height_ = height;

    glTexImage2DMultisample(GetTextureTargetPrimitive(),
                            sample_count_,
                            GetTextureInternalFormatPrimitive(),
                            width, height,
                            GL_TRUE);

    Unbind();
}

}
