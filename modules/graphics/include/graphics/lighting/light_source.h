#ifndef DUCK_LIGHT_SOURCE_H
#define DUCK_LIGHT_SOURCE_H

#include <graphics/shaders/data/shader_data.h>

#include <graphics/shaders/data/shader_data.h>
#include <graphics/shaders/program.h>

#include <math/math_ifx.h>
#include <math/transform.h>

#include <memory>

namespace ifx {

struct LightParams {
    glm::vec3 ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);

    // Attenuation
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.0032;

    // FlashLight cutOff angle, in degrees
    float cutOff = 22.5;
    float outerCutOff = 27.5;
};

enum class LightType {
    DIRECTIONAL, POINT, SPOTLIGHT
};

/*
 * Light source. Can be rendered if mesh was provided.
 * Light source can be bound if RenderObject and thus follow its position.
 *
 * Each light has its Attenuation values stored in Light struct.
 * The attenuation can be omitted by the shader itself.
 */
class LightSource : public Transformable {
public:
    LightSource(const LightParams &light, LightType type);
    virtual ~LightSource();

    LightParams &light_params() { return light_params_; }
    LightType light_type() { return light_type_; }
    bool cast_shadow() { return cast_shadow_; }
    void cast_shadow(bool v) { cast_shadow_ = v; }

    static std::string LightTypeString(LightType type);

    void SetLightParams(const LightParams &light);

    /*
     * The id is used to separated lights of the same type in the shaders.
     */
    void use(const Program &program, int id = -1);

protected:
    /*
     * Derived classes should implement special binding mechanism.
     * Such as binding direction for directional light.
     */
    virtual void bind(const Program &program, int id = -1) = 0;

    LightParams light_params_;
    LightType light_type_;

    bool cast_shadow_;
};
}

#endif //DUCK_LIGHT_SOURCE_H
