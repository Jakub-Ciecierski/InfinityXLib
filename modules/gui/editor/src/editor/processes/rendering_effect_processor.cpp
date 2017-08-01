#include "editor/processes/rendering_effect_processor.h"

#include <game/resources/resource_context.h>

#include <graphics/rendering/scene_renderer.h>
#include <graphics/rendering/rendering_effect.h>
#include <graphics/shaders/program_creator.h>

#include <resources/resource_manager.h>
#include <resources/resources.h>

#include <boost/filesystem.hpp>

#include <iostream>
#include <graphics/shaders/loaders/program_loader.h>

namespace ifx {

RenderingEffectProcessor::RenderingEffectProcessor(
        std::shared_ptr<ResourceContext> resource_context,
        std::shared_ptr<SceneRenderer> scene_renderer) :
        resource_context_(resource_context),
        scene_renderer_(scene_renderer) {
    CompileAllPrograms();
}

std::vector<std::shared_ptr<RenderingEffect>>
RenderingEffectProcessor::CompileAllRenderingEffects(){
    std::vector<std::shared_ptr<RenderingEffect>> rendering_effects;

    auto root_directory
            = resource_context_->resource_manager()->resource_path()->GetResourceRoot(ResourceType::SHADER);
    boost::filesystem::path root_path(root_directory);
    boost::filesystem::recursive_directory_iterator iterator(root_path);
    for(auto&& dir : iterator){
        if (IsValidProgramDirectory(dir.path().string())) {
            ifx::ProgramLoader program_loader(resource_context_->program_creator());
            try{
                auto shader_paths = GetShaderPaths(dir);
                auto program = program_loader.CreateProgram(shader_paths);
                rendering_effects.push_back(std::make_shared<RenderingEffect>(
                        program,
                        RenderingState{},
                        GetDifference(dir.path().string(), root_directory)));
            }catch(const std::invalid_argument& e){
                std::cout << e.what() << std::endl;
            }
        }
    }

    return rendering_effects;
}

void RenderingEffectProcessor::CompileAllPrograms(){
    auto rendering_effects = CompileAllRenderingEffects();
    auto current_rendering_effects = scene_renderer_ ->rendering_effects();
    for(auto& rendering_effect : rendering_effects) {
        bool exists = false;
        for (auto &current_rendering_effect: current_rendering_effects) {
            if (current_rendering_effect== rendering_effect)
                continue;
            if (current_rendering_effect->name() == rendering_effect->name())
                exists = true;
        }
        if(!exists)
            scene_renderer_->Add(rendering_effect);
    }

}

bool RenderingEffectProcessor::IsValidProgramDirectory(const std::string dir_name){
    return EndsWith(dir_name, ".prog");
}

ShaderPaths RenderingEffectProcessor::GetShaderPaths(boost::filesystem::directory_entry dir){
    boost::filesystem::directory_iterator dir_iterator(dir);
    ShaderPaths shader_paths;
    for(auto&& file : dir_iterator){
        auto string_path = file.path().string();
        switch(GetShaderType(string_path)){
            case ShaderType::Vertex:
                shader_paths.vertex_path = string_path;
                break;
            case ShaderType::Fragment:
                shader_paths.fragment_path = string_path;
                break;
            case ShaderType::Geometry:
                shader_paths.geometry_path = string_path;
                break;
            case ShaderType::TessControl:
                shader_paths.tcs_path = string_path;
                break;
            case ShaderType::TessEvaluation:
                shader_paths.tes_path = string_path;
                break;
        }
    }
    return shader_paths;
}

ShaderType RenderingEffectProcessor::GetShaderType(const std::string& filename){
    if(EndsWith(filename, ".vs"))
        return ShaderType::Vertex;
    else if(EndsWith(filename, ".fs"))
        return ShaderType::Fragment;
    else if(EndsWith(filename, ".gs"))
        return ShaderType::Geometry;
    else if(EndsWith(filename, ".tcs"))
        return ShaderType::TessControl;
    else if(EndsWith(filename, ".tes"))
        return ShaderType::TessEvaluation;
    else
        throw std::invalid_argument("Invalid shader extension");
}

bool RenderingEffectProcessor::EndsWith(const std::string &str,
                                        const std::string &end) {
    auto program_extension_length = end.length();
    auto dir_name_length = str.length();

    auto substr = str.substr(dir_name_length - program_extension_length,
                                  program_extension_length);

    return substr == end;
}

std::string RenderingEffectProcessor::GetDifference(const std::string& str1,
                                                    const std::string& str2){
    std::string difference;
    if(str1.length() < str2.length())
        return difference;

    for(unsigned int i = 0; i < str1.length(); i++){
        if(i >= str2.length()){
            if(str1[i] != '/')
                difference += str1[i];
        }

    }
    return difference;
}

}