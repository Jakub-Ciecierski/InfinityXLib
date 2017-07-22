#include "editor/views/scene_views/game_component_views/light_view.h"

#include <graphics/lighting/light_source.h>
#include <graphics/rendering/shadows/shadow_mapping.h>
#include <graphics/lighting/types/light_directional.h>

#include <gui/imgui/imgui.h>

namespace ifx{

LightView::LightView(){}
LightView::~LightView(){}

void LightView::Render(std::shared_ptr<LightSource> light_source){
    std::string display = "Light";
    display += " [";
    display += LightSource::LightTypeString(light_source->light_type());
    display += "]";

    if(ImGui::TreeNode(display.c_str())){
        RenderColor(light_source);

        ImGui::PushItemWidth(150);
        {
            RenderAttenuation(light_source);
            RenderSpotlight(light_source);
            RenderShadowMapping(light_source);
        }
        ImGui::PopItemWidth();

        ImGui::TreePop();
    }

}

void LightView::RenderColor(std::shared_ptr<LightSource> light_source){
    if(ImGui::TreeNode("Color")){
        RenderColorAmbient(light_source);
        RenderColorDiffuse(light_source);
        RenderColorSpecular(light_source);

        ImGui::TreePop();
    }

}
void LightView::RenderColorAmbient(std::shared_ptr<LightSource> light_source){
    LightParams& light_params = light_source->light_params();

    static float raw[3];
    glm::vec3& v = light_params.ambient;
    raw[0] = v.x;
    raw[1] = v.y;
    raw[2] = v.z;
    ImGui::ColorEdit3("Ambient", raw);
    //ImGui::SliderFloat3("Ambient", raw, 0, 1);
    v = glm::vec3(raw[0], raw[1], raw[2]);
}

void LightView::RenderColorDiffuse(std::shared_ptr<LightSource> light_source){
    LightParams& light_params = light_source->light_params();

    static float raw[3];
    glm::vec3& v = light_params.diffuse;
    raw[0] = v.x;
    raw[1] = v.y;
    raw[2] = v.z;
    ImGui::ColorEdit3("Diffuse", raw);
    //ImGui::SliderFloat3("Diffuse", raw, 0, 1);
    v = glm::vec3(raw[0], raw[1], raw[2]);
}

void LightView::RenderColorSpecular(std::shared_ptr<LightSource> light_source){
    LightParams& light_params = light_source->light_params();

    static float raw[3];
    glm::vec3& v = light_params.specular;
    raw[0] = v.x;
    raw[1] = v.y;
    raw[2] = v.z;
    ImGui::ColorEdit3("Specular", raw);
    //ImGui::SliderFloat3("Specular", raw, 0, 1);
    v = glm::vec3(raw[0], raw[1], raw[2]);
}

void LightView::RenderAttenuation(std::shared_ptr<LightSource> light_source){
    if(ImGui::TreeNode("Attenuation")){
        RenderAttenuationConstant(light_source);
        RenderAttenuationLinear(light_source);
        RenderAttenuationQuadratic(light_source);

        ImGui::TreePop();
    }
}

void LightView::RenderAttenuationConstant(
        std::shared_ptr<LightSource> light_source){
    LightParams& light_params = light_source->light_params();

    ImGui::SliderFloat("Contant", &light_params.constant, 0, 1);
}
void LightView::RenderAttenuationLinear(
        std::shared_ptr<LightSource> light_source){
    LightParams& light_params = light_source->light_params();

    ImGui::SliderFloat("Linear", &light_params.linear, 0, 1);
}
void LightView::RenderAttenuationQuadratic(
        std::shared_ptr<LightSource> light_source){
    LightParams& light_params = light_source->light_params();

    ImGui::SliderFloat("Quadratic", &light_params.quadratic, 0, 1);
}

void LightView::RenderSpotlight(std::shared_ptr<LightSource> light_source){
    if(light_source->light_type() != LightType::SPOTLIGHT) return;

    LightParams& light_params = light_source->light_params();
    if(ImGui::TreeNode("Cut off [degrees]")){
        ImGui::SliderFloat("Inner Cut off", &light_params.cutOff, 0, 360);
        ImGui::SliderFloat("Outer Cut off", &light_params.outerCutOff, 0, 360);

        ImGui::TreePop();
    }
}

void LightView::RenderShadowMapping(
        std::shared_ptr<LightSource> light_source){
    if(light_source->light_type() != LightType::SPOTLIGHT
       && light_source->light_type() != LightType::DIRECTIONAL) return;

    if(ImGui::TreeNode("Shadow Mapping")){
        RenderShadowMappingCastShadow(
                std::static_pointer_cast<LightDirectional>(light_source));
        RenderShadowMappingProjectionParameters(
                std::static_pointer_cast<LightDirectional>(light_source));
        RenderShadowMappingResolution(
                std::static_pointer_cast<LightDirectional>(light_source));
        ImGui::TreePop();
    }
}

void LightView::RenderShadowMappingCastShadow(
        std::shared_ptr<LightDirectional> light_source){
    static bool raw;
    raw = light_source->cast_shadow();
    if(ImGui::Checkbox("Cast Shadow", &raw)){
        light_source->cast_shadow(raw);
    }
}

void LightView::RenderShadowMappingProjectionParameters(
        std::shared_ptr<LightDirectional> light_source){
    auto& projection_parameters
            = light_source->shadow_mapping()->projection_parameters();
    if(ImGui::TreeNode("Projection Parameters")){

        ImGui::SliderFloat("Near Plane", &projection_parameters.near_plane,
                           0.1f, 100.0f);
        ImGui::SliderFloat("Far Plane", &projection_parameters.far_plane,
                           1.0f, 200.0f);

        ImGui::TreePop();
    }
}

void LightView::RenderShadowMappingResolution(
        std::shared_ptr<LightDirectional> light_source){
    const auto& dimensions = light_source->shadow_mapping()->dimensions();
    static float height;
    static float width;
    height = dimensions.height;
    width = dimensions.width;

    if(ImGui::TreeNode("Resolution")){
        bool width_changed
                = ImGui::SliderFloat("Width", &width, 50.0f, 4080.0f);
        bool height_changed
                = ImGui::SliderFloat("Height", &height, 50.0f, 4080.0f);

        if(width_changed || height_changed){
            light_source->shadow_mapping()->Reset(
                    Dimensions{width, height});
        }

        ImGui::TreePop();
    }
}

}
