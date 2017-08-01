#ifndef PROJECT_RENDERING_EFFECT_PROCESSOR_H
#define PROJECT_RENDERING_EFFECT_PROCESSOR_H

#include <memory>
#include <vector>
#include <boost/filesystem.hpp>

namespace ifx {

class RenderingEffect;
class ResourceContext;
class SceneRenderer;
struct ShaderPaths;
enum class ShaderType;

/**
 * Browses the shader resources directory
 * and creates RenderingEffects based on them.
 */
class RenderingEffectProcessor {
public:
    RenderingEffectProcessor(std::shared_ptr<ResourceContext> resource_context,
                             std::shared_ptr<SceneRenderer> scene_renderer);
    ~RenderingEffectProcessor() = default;

    std::shared_ptr<SceneRenderer> scene_renderer(){return scene_renderer_;}

    void CompileAllPrograms();

private:
    std::vector<std::shared_ptr<RenderingEffect>> CompileAllRenderingEffects();

    bool IsValidProgramDirectory(const std::string dir_name);

    ShaderPaths GetShaderPaths(boost::filesystem::directory_entry dir);
    ShaderType GetShaderType(const std::string& filename);

    bool EndsWith(const std::string& str,
                  const std::string& end);

    std::string GetDifference(const std::string& str1,
                              const std::string& str2);

    std::shared_ptr<ResourceContext> resource_context_;
    std::shared_ptr<SceneRenderer> scene_renderer_;

};
}

#endif //PROJECT_RENDERING_EFFECT_PROCESSOR_H
