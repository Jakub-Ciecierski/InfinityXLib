#ifndef PROJECT_MATERIAL_H
#define PROJECT_MATERIAL_H

#include <shaders/textures/texture.h>

#include <memory>

namespace ifx {

struct Material {
    float shininess = 32.0f;
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
