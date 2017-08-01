#ifndef PROJECT_RENDERING_EFFECT_VIEW_H
#define PROJECT_RENDERING_EFFECT_VIEW_H

#include <vector>
#include <memory>

class Shader;
struct ShaderError;

namespace ifx {

class RenderingEffect;

class RenderingEffectView {
public:
    RenderingEffectView();
    ~RenderingEffectView() = default;

    void Render(const std::vector<std::shared_ptr<RenderingEffect>>& rendering_effects);
private:
    void RenderList(const std::vector<std::shared_ptr<RenderingEffect>>& rendering_effects);

    void RenderShaders(std::shared_ptr<RenderingEffect> rendering_effect);
    void RenderShaderReload(std::shared_ptr<RenderingEffect> rendering_effect);
    void RenderShader(Shader* shader, std::string shader_type_name);
    void RenderShaderWindow(Shader* shader, bool open);
    void RenderErrorWindow(const ShaderError& shader_error);

    void RenderState(std::shared_ptr<RenderingEffect> rendering_effect);

    std::string GetBaseName(const std::string& name);
    std::string GetBaseShaderName(const std::string& name);

    bool render_error_window_;
    std::string shader_error_message_;

    std::shared_ptr<RenderingEffect> selected_rendering_effect_;
};
}

#endif //PROJECT_RENDERING_EFFECT_VIEW_H
