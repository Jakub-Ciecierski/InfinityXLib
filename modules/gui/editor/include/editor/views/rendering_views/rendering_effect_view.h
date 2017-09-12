#ifndef PROJECT_RENDERING_EFFECT_VIEW_H
#define PROJECT_RENDERING_EFFECT_VIEW_H

#include <vector>
#include <memory>

class Shader;
struct ShaderError;

namespace ifx {

class RenderingEffect;
class RenderingEffectProcessor;
class Program;

class RenderingEffectView {
public:
    RenderingEffectView(
        std::shared_ptr<RenderingEffectProcessor> rendering_effect_processor);
    ~RenderingEffectView() = default;

    void Render(const std::vector<std::shared_ptr<RenderingEffect>> &rendering_effects);
private:
    void RenderReloadProject();

    void RenderList(const std::vector<std::shared_ptr<RenderingEffect>> &rendering_effects);

    void RenderInspector(std::shared_ptr<RenderingEffect> rendering_effect);

    void RenderShaders(std::shared_ptr<RenderingEffect> rendering_effect);
    void RenderShaderReload(std::shared_ptr<RenderingEffect> rendering_effect);
    void RenderShader(Shader *shader,
                      std::shared_ptr<Program> program,
                      std::string shader_type_name);
    void RenderShaderWindow(Shader *shader,
                            std::shared_ptr<Program> program,
                            bool open);
    void RenderErrorWindow(const ShaderError &shader_error);

    void RenderState(std::shared_ptr<RenderingEffect> rendering_effect);

    std::string GetBaseName(const std::string &name);
    std::string GetBaseShaderName(const std::string &name);

    std::shared_ptr<RenderingEffectProcessor> rendering_effect_processor_;
    std::shared_ptr<RenderingEffect> selected_rendering_effect_;

    bool render_error_window_;
    std::string shader_error_message_;
};
}

#endif //PROJECT_RENDERING_EFFECT_VIEW_H
