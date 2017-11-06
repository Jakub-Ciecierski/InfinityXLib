#include "graphics/model/material.h"

namespace ifx {

void Material::AddTexture(std::shared_ptr<Texture2D> texture) {
    if (texture && texture->texture_type() == TextureTypes::DIFFUSE)
        diffuse = texture;
    if (texture && texture->texture_type() == TextureTypes::SPECULAR)
        specular = texture;
    if (texture && texture->texture_type() == TextureTypes::NORMAL)
        normal = texture;
    if (texture && texture->texture_type() == TextureTypes::DISPLACEMENT)
        displacement = texture;
    if (texture && texture->texture_type() == TextureTypes::FBO)
        fbo = texture;
}

void Material::AddTexture(std::shared_ptr<Texture2D> texture, TextureTypes type){
    if (type == TextureTypes::DIFFUSE)
        diffuse = texture;
    if (type == TextureTypes::SPECULAR)
        specular = texture;
    if (type == TextureTypes::NORMAL)
        normal = texture;
    if (type == TextureTypes::DISPLACEMENT)
        displacement = texture;
    if (type == TextureTypes::FBO)
        fbo = texture;
}

} // namespace ifx