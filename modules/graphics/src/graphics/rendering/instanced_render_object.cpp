#include "graphics/rendering/instanced_render_object.h"

#include <graphics/model/mesh.h>
#include <graphics/model/model.h>

namespace ifx {

InstancedRenderObject::InstancedRenderObject(std::shared_ptr<Model> model,
                                             InstancedData& instanced_data) :
    RenderObject(model),
    instanced_data_(instanced_data) {
    const std::vector<Mesh*>& meshes = model->getMeshes();
    for(unsigned int i = 0; i < meshes.size(); i++){
        VAO* vao = meshes[i]->vao();
        vao->bindInstancedRenderingBuffers(instanced_data);
    }
}

InstancedRenderObject::~InstancedRenderObject(){}

void InstancedRenderObject::Render(const Program& program){
    if(before_render_)
        before_render_(&program);

    program.use();

    // Model
    GLint transformLoc = glGetUniformLocation(program.getID(),
                                              MODEL_MATRIX_NAME.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
                       glm::value_ptr(GetModelMatrix()));

    for(auto& model : models_)
        model->drawInstanced(program, instanced_data_.data_count);

    if(after_render_)
        after_render_(&program);
}

} // namespace ifx