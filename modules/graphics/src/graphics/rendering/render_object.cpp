#include <graphics/rendering/render_object.h>

#include <graphics/model/model.h>

#include <GL/glew.h>

using namespace glm;

namespace ifx {

RenderObject::RenderObject(std::shared_ptr<Model> model) :
        do_render_(true) {
    models_.push_back(model);
}

RenderObject::RenderObject(std::vector<std::shared_ptr<Model>> models) :
        models_(models),
        do_render_(true){
}

RenderObject::~RenderObject() { }

void RenderObject::SetBeforeRender(
        std::function<void(const Program *program)> before_render) {
    before_render_ = before_render;
}

void RenderObject::SetAfterRender(
        std::function<void(const Program *program)> after_render) {
    after_render_ = after_render;
}

void RenderObject::addProgram(std::shared_ptr<Program> program) {
    programs_.push_back(program);
}

void RenderObject::Render(const Program &program) {
    if (!do_render_)
        return;
    if (before_render_)
        before_render_(&program);

    program.use();

    // Model
    GLint transformLoc = glGetUniformLocation(program.getID(),
                                              MODEL_MATRIX_NAME.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(GetModelMatrix()));

    for(auto& model : models_)
        model->draw(program);

    if (after_render_)
        after_render_(&program);
}

void RenderObject::RegisterRenderingEffect(RenderingEffect* rendering_effect){
    rendering_effects_.push_back(rendering_effect);
}

void RenderObject::DeregisterRenderingEffect(RenderingEffect* rendering_effect){
    for(unsigned int i = 0; i < rendering_effects_.size(); i++){
        if(rendering_effects_[i] == rendering_effect){
            rendering_effects_.erase(rendering_effects_.begin() + i);
        }
    }
}

}