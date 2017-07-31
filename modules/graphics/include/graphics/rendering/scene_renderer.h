#ifndef PROJECT_SCENE_RENDERER_H
#define PROJECT_SCENE_RENDERER_H

#include <memory>
#include <vector>

namespace ifx {

class Program;
class Camera;
class LightGroup;
class LightSource;
class RenderObject;
class RenderingEffect;

/**
 * Renders the scene with lights and camera
 */
class SceneRenderer {
public:

    SceneRenderer();
    ~SceneRenderer();

    const std::vector<std::shared_ptr<RenderingEffect>>& rendering_effects(){
            return rendering_effects_;}
    const std::vector<std::shared_ptr<RenderObject>>& render_objects() {
        return render_objects_;}
    const std::shared_ptr<LightGroup> light_group() const {return light_group_;}
    const std::shared_ptr<Camera> camera(){return camera_;}

    void Render() const;
    void Render(const std::shared_ptr<Program> program) const;

    void Add(std::shared_ptr<RenderingEffect> rendering_effect);
    void Add(std::shared_ptr<RenderObject> render_object);
    void Add(std::shared_ptr<LightSource> light_source);
    void Add(std::shared_ptr<Camera> camera);

    bool Remove(std::shared_ptr<RenderingEffect> rendering_effect);
    bool Remove(std::shared_ptr<RenderObject> render_object);
    bool Remove(std::shared_ptr<LightSource> light_source);
    bool Remove(std::shared_ptr<Camera> camera);

private:
    void Render(std::shared_ptr<RenderObject> render_object) const;

    std::vector<std::shared_ptr<RenderingEffect>> rendering_effects_;

    std::vector<std::shared_ptr<RenderObject>> render_objects_;
    std::shared_ptr<LightGroup> light_group_;
    std::shared_ptr<Camera> camera_;
};

}

#endif //PROJECT_SCENE_RENDERER_H

