#include "engine_gui/views/scene_view/game_component_views/camera_view.h"

#include <graphics/rendering/camera/camera.h>
#include <game/components/cameras/camera_component.h>

namespace ifx{

CameraView::CameraView(){}
CameraView::~CameraView(){}

void CameraView::Render(std::shared_ptr<CameraComponent> camera){}

}