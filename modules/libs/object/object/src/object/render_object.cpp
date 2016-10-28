#include "object/render_object.h"

using namespace glm;

RenderObject::RenderObject(ObjectID id,
                           std::shared_ptr<Model> model) :
        ifx::MovableObject(id),
        model_(model),
        do_render_(true){}

RenderObject::~RenderObject(){}

void RenderObject::SetBeforeRender(
        std::function<void(const Program* program)> before_render){
    before_render_ = before_render;
}
void RenderObject::SetAfterRender(
        std::function<void(const Program* program)> after_render){
    after_render_ = after_render;
}

void RenderObject::addProgram(std::shared_ptr<Program> program){
    programs_.push_back(program);
}

void RenderObject::render(const Program& program){
    if(!do_render_)
        return;
    if(before_render_)
        before_render_(&program);

    program.use();

    // Model
    GLint transformLoc = glGetUniformLocation(program.getID(),
                                              MODEL_MATRIX_NAME.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(ModelMatrix));

    model_->draw(program);

    if(after_render_)
        after_render_(&program);
}