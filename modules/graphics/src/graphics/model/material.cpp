#include "graphics/model/material.h"

namespace ifx {

void Material::AddTexture(std::shared_ptr<Texture2D> texture) {
    if(texture->texture_type() == TextureTypes::DIFFUSE)
        diffuse = texture;
    if(texture->texture_type() == TextureTypes::SPECULAR)
        specular = texture;
    if(texture->texture_type() == TextureTypes::NORMAL)
        normal = texture;
    if(texture->texture_type() == TextureTypes::DISPLACEMENT)
        displacement = texture;
    if(texture->texture_type() == TextureTypes::FBO)
        fbo = texture;
}

} // namespace ifx