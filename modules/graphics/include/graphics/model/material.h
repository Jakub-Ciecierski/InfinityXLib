#ifndef PROJECT_MATERIAL_H
#define PROJECT_MATERIAL_H

#include <graphics/shaders/textures/texture.h>

#include <memory>

namespace ifx {

struct Material {
    float shininess = 32.0f;
    float alpha = 1.0f; // use < 0 if you want to the texture to override it.

    std::shared_ptr<Texture2D> diffuse;
    std::shared_ptr<Texture2D> specular;
    std::shared_ptr<Texture2D> normal;
    std::shared_ptr<Texture2D> displacement;
    std::shared_ptr<Texture2D> fbo;

    /**
     * Adds texture to appropriate type slot
     */
    void AddTexture(std::shared_ptr<Texture2D> texture);
};
}

#endif //PROJECT_MATERIAL_H
