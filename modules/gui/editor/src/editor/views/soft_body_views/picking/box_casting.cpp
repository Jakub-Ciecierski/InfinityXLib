#include "editor/views/soft_body_views/picking/box_casting.h"

#include "editor/views/soft_body_views/picking/rendering_spaces.h"

#include <game/components/render/render_component.h>

#include <graphics/model/model.h>
#include <graphics/model/mesh.h>
#include <graphics/shaders/data/shader_data.h>
#include <graphics/shaders/buffers/vbo.h>

namespace ifx {

BoxCasting::BoxCasting(std::shared_ptr<RenderComponent> render_component) :
    box_render_component_(render_component),
    box_viewport_(BoxViewport{
        glm::vec2(),
        glm::vec2(),
        glm::vec2(),
        glm::vec2()}),
    window_width_(0),
    window_height_(0),
    view_(glm::mat4()),
    projection_(glm::mat4()){
    box_render_component_->do_render(false);
}

void BoxCasting::Begin(const glm::vec2& viewport_position){
    box_viewport_.a_start = viewport_position;
    box_render_component_->do_render(true);
}

void BoxCasting::Finish(){
    box_render_component_->do_render(false);
}

void BoxCasting::SetEndViewport(const glm::vec2& viewport_position) {
    box_viewport_.d_end = viewport_position;
    CalculateBoxPositions();
    UpdateHomogeneousClipSpaceRenderingComponent();
}

void BoxCasting::CalculateBoxPositions(){
    box_viewport_.b_interpolated = glm::vec2(box_viewport_.d_end.x,
                                             box_viewport_.a_start.y);
    box_viewport_.c_interpolated = glm::vec2(box_viewport_.a_start.x,
                                             box_viewport_.d_end.y);
}

void BoxCasting::UpdateHomogeneousClipSpaceRenderingComponent(){
    auto va = ToHomogeneousClipSpace(box_viewport_.a_start);
    auto vb = ToHomogeneousClipSpace(box_viewport_.b_interpolated);
    auto vc = ToHomogeneousClipSpace(box_viewport_.c_interpolated);
    auto vd = ToHomogeneousClipSpace(box_viewport_.d_end);

    auto* vbo = box_render_component_->models()[0]->getMesh(0)->vbo();
    auto* vertices = vbo->vertices();
    (*vertices)[0].Position = glm::vec3(vb);
    (*vertices)[1].Position = glm::vec3(vd);
    (*vertices)[2].Position = glm::vec3(vc);
    (*vertices)[3].Position = glm::vec3(va);

    vbo->Update();
}

glm::vec4 BoxCasting::ToHomogeneousClipSpace(const glm::vec2& a){
    auto nds = ViewPortSpace2NormalisedDeviceSpace(a,
                                                   window_width_,
                                                   window_height_);
    auto clip = NormalisedDeviceSpace2HomogeneousClipSpace(nds);

    return clip;
}

}