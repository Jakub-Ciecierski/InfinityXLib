#ifndef PROJECT_SHADOW_MAPPING_H
#define PROJECT_SHADOW_MAPPING_H

#include <memory>

#include <graphics/shaders/textures/texture.h>
#include <graphics/shaders/data/shader_data.h>
#include <math/math_ifx.h>

namespace ifx {

class Program;
class FBO;
class LightDirectional;
class Scene;
class SceneRenderer;
class TextureCreator;

struct ProjectionParameters{
    float near_plane = 0.1f;
    float far_plane = 100.0f;

    float left = -10.0f;
    float right = 10.0f;
    float bottom = -10.0f;
    float up = 10.0f;
};

/**
 * Creates Shadows in the scene using the Shadow Mapping technique.
 *
 * Only Directional Lights are supported in this Shadow Map version.
 *
 * Creates FBO with Depth Buffer only. Then, renders the scene to texture
 * from the light's perspective, writing only the depth (z).
 *
 * Creates Light Projection Matrix based on light's position and the
 * orthogonal projection.
 */
class ShadowMapping {
public:
    ShadowMapping(Dimensions dimensions,
                  std::shared_ptr<Program> program,
                  std::shared_ptr<TextureCreator> texture_creator);
    ~ShadowMapping();

    FBO* fbo(){return fbo_.get();}

    const Dimensions& dimensions(){return dimensions_;}
    ProjectionParameters& projection_parameters(){
        return projection_parameters_;}

    /**
     * Renders the scene in light's space, writing only depth buffer.
     * Changed Viewport
     */
    void Render(const std::shared_ptr<SceneRenderer> scene,
                LightDirectional* light);

    glm::mat4 GetLightSpaceMatrix(LightDirectional* light);

    void Reset(Dimensions&& new_dimensions);

private:
    std::shared_ptr<Texture2D> CreateTexture();
    void InitFBO(std::shared_ptr<Texture2D> texture);

    void BindLightMatrix(const Program* program, LightDirectional* light);

    std::unique_ptr<FBO> fbo_;

    std::shared_ptr<Program> program_;

    /**
     * Dimensions of the shadow map. Used to create texture
     */
    Dimensions dimensions_;
    ProjectionParameters projection_parameters_;

    glm::mat4 light_projection_;
    glm::mat4 light_view_;
    glm::mat4 light_MVP_;

    std::shared_ptr<TextureCreator> texture_creator_;
};
}

#endif //PROJECT_SHADOW_MAPPING_H
