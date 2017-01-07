#ifndef DUCK_LIGHT_GROUP_H
#define DUCK_LIGHT_GROUP_H

#include <graphics/lighting/types/light_point.h>
#include <graphics/lighting/types/light_spotlight.h>

#include <vector>

#include <memory>

namespace ifx {
/*
 * LightGroup combines all lights in the scene and renders them using
 * one shader.
 *
 * Moreover LightGroup takes ownership of all Lights.
 * If a LightSource is removed, then LightGroup also losed owner ship of it
 */
class LightGroup {
public:

    LightGroup();
    ~LightGroup();

    const std::vector<std::shared_ptr<LightSource>>& lights() const {
        return lights_;}

    const std::vector<std::shared_ptr<LightDirectional>>
            GetDirectionalLights() const;

    void Add(std::shared_ptr<LightSource> light_source);
    bool Remove(std::shared_ptr<LightSource> light_source);

    /*
     * Uses all lights. Binds all the data with the shaders
     */
    void use(const Program &program);

    /*
     * Renders all LightSources
     */
    void render(const Program &program);

private:
    /*
    * Binds the number of each light type with the shader
    */
    void bindLightCount(const Program &program);

    std::vector<std::shared_ptr<LightSource>> lights_;

    int point_light_count_;
    int spotlight_light_count_;
    int directional_light_count_;

};
}

#endif //DUCK_LIGHT_GROUP_H
