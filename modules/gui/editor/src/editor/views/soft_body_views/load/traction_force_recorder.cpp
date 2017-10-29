#include "editor/views/soft_body_views/load/traction_force_recorder.h"

#include <editor/views/soft_body_views/picking/rendering_spaces.h>

#include <game/components/render/render_component.h>

#include <graphics/model/model.h>

namespace ifx {

TractionForceRecorder::TractionForceRecorder(
    std::shared_ptr<RenderComponent> render_component) :
    render_component_(render_component),
    is_active_(false){}

void TractionForceRecorder::Begin(const glm::vec2& viewport_position_begin){
    is_active_ = true;
    viewport_position_begin_ = viewport_position_begin;

    render_component_->do_render(true);
}

void TractionForceRecorder::Update(float window_width,
                                   float window_height,
                                   const glm::vec2 &viewport_position) {
    window_width_ = window_width;
    window_height_ = window_height;
    viewport_position_end_ = viewport_position;

    auto clip_space1 = ToHomogeneousClipSpace(viewport_position_begin_);
    auto clip_space2 = ToHomogeneousClipSpace(viewport_position_end_);

    auto* vbo = render_component_->models()[0]->getMesh(0)->vbo();
    auto* vertices = vbo->vertices();
    (*vertices)[0].Position = glm::vec3(clip_space1);
    (*vertices)[1].Position = glm::vec3(clip_space2);

    vbo->Update();
}

void TractionForceRecorder::End(){
    is_active_ = false;
    render_component_->do_render(false);
}

float TractionForceRecorder::GetMagnitude(){
    auto difference = viewport_position_end_ - viewport_position_begin_;
    return difference.x + difference.y;
}

glm::vec4 TractionForceRecorder::ToHomogeneousClipSpace(const glm::vec2& a){
    auto nds = ViewPortSpace2NormalisedDeviceSpace(a,
                                                   window_width_,
                                                   window_height_);
    auto clip = NormalisedDeviceSpace2HomogeneousClipSpace(nds);

    return clip;
}

}