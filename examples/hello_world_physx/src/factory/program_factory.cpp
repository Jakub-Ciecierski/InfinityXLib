#include "factory/program_factory.h"

#include <graphics/shaders/loaders/program_loader.h>
#include <graphics/shaders/program_creator.h>

#include <resources/resource_manager.h>
#include <resources/resources.h>

namespace ifx {

ProgramFactory::ProgramFactory(
    std::shared_ptr<ProgramCreator> program_creator) :
    program_creator_(program_creator) {}

ProgramFactory::~ProgramFactory() {}

std::shared_ptr<Program> ProgramFactory::LoadMainProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();

    std::string vertex_path =
        resource_path->GetResourcePath("main/main.vs",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("main/main.fs",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path);
}

std::shared_ptr<Program> ProgramFactory::LoadMainNormalMappingProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();

    std::string vertex_path =
        resource_path->GetResourcePath("main/normal_mapping/main.vs",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("main/normal_mapping/main.fs",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path);
}

std::shared_ptr<Program> ProgramFactory::LoadHeightmapProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();

    std::string vertex_path =
        resource_path->GetResourcePath("heightmap/heightmap.vs",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("heightmap/heightmap.fs",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path);
}

std::shared_ptr<Program> ProgramFactory::LoadCAMMaterialBoxProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();

    std::string vertex_path =
        resource_path->GetResourcePath(
            "cam/cam_material_box/cam_material_box.vs",
            ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath(
            "cam/cam_material_box/cam_material_box.fs",
            ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path);
}

std::shared_ptr<Program> ProgramFactory::LoadCAMPlane() {
    auto resource_path = program_creator_->resource_manager()->resource_path();
    std::string vertex_path =
        resource_path->GetResourcePath("cam/plane/tess.vs",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("cam/plane/tess.fs",
                                       ifx::ResourceType::SHADER);
    std::string tcs_path =
        resource_path->GetResourcePath("cam/plane/tess.tcs",
                                       ifx::ResourceType::SHADER);
    std::string tes_path =
        resource_path->GetResourcePath("cam/plane/tess.tes",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(
        vertex_path, fragment_path, tcs_path, tes_path);
}

std::shared_ptr<Program> ProgramFactory::LoadInstancedProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();

    std::string vertex_path =
        resource_path->GetResourcePath("instanced_rendering/instanced.vs",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("instanced_rendering/instanced.fs",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path);
}

std::shared_ptr<Program> ProgramFactory::LoadShadowMappingProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();

    std::string vertex_path =
        resource_path->GetResourcePath("shadow_mapping/shadow_mapping.vs",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("shadow_mapping/shadow_mapping.fs",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path);
}

std::shared_ptr<Program> ProgramFactory::LoadFBOProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();

    std::string vertex_path =
        resource_path->GetResourcePath("fbo/fbo.vs", ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("fbo/fbo.fs", ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path);
}

std::shared_ptr<Program> ProgramFactory::LoadNormalVisionProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();

    std::string vertex_path =
        resource_path->GetResourcePath("geo_normal/norm.vs",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("geo_normal/norm.fs",
                                       ifx::ResourceType::SHADER);
    std::string geometry_path =
        resource_path->GetResourcePath("geo_normal/norm.gs",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(
        vertex_path, fragment_path, geometry_path);
}

std::shared_ptr<Program> ProgramFactory::loadTessellationLODProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();
    std::string vertex_path =
        resource_path->GetResourcePath("tessellation/lod/tess.vs",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("tessellation/lod/tess.fs",
                                       ifx::ResourceType::SHADER);
    std::string tcs_path =
        resource_path->GetResourcePath("tessellation/lod/tess.tcs",
                                       ifx::ResourceType::SHADER);
    std::string tes_path =
        resource_path->GetResourcePath("tessellation/lod/tess.tes",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path,
                                                         tcs_path, tes_path);
}

std::shared_ptr<Program> ProgramFactory::loadTessellationBicubicBezierPolygonProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();

    std::string vertex_path =
        resource_path->GetResourcePath
            ("tessellation/bicubic_bezier/polygon/tess.vs",
             ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath
            ("tessellation/bicubic_bezier/polygon/tess.fs",
             ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path);
}

std::shared_ptr<Program> ProgramFactory::loadTessellationBicubicBezierProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();
    std::string vertex_path =
        resource_path->GetResourcePath("tessellation/bicubic_bezier/tess.vs",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("tessellation/bicubic_bezier/tess.fs",
                                       ifx::ResourceType::SHADER);
    std::string tcs_path =
        resource_path->GetResourcePath("tessellation/bicubic_bezier/tess.tcs",
                                       ifx::ResourceType::SHADER);
    std::string tes_path =
        resource_path->GetResourcePath("tessellation/bicubic_bezier/tess.tes",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path,
                                                         tcs_path, tes_path);
}

std::shared_ptr<Program> ProgramFactory::loadTessellationProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();
    std::string vertex_path =
        resource_path->GetResourcePath("tessellation/tess.vs",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("tessellation/tess.fs",
                                       ifx::ResourceType::SHADER);
    std::string tcs_path =
        resource_path->GetResourcePath("tessellation/tess.tcs",
                                       ifx::ResourceType::SHADER);
    std::string tes_path =
        resource_path->GetResourcePath("tessellation/tess.tes",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path,
                                                         tcs_path, tes_path);
}

std::shared_ptr<Program> ProgramFactory::loadAllLightProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();

    std::string vertex_path =
        resource_path->GetResourcePath("lighting/light_all_vert.glsl",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("lighting/light_all_frag.glsl",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path);
}

std::shared_ptr<Program> ProgramFactory::loadAnisotropicLightProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();

    std::string vertex_path =
        resource_path->GetResourcePath("lighting/anis_light_vert.glsl",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("lighting/anis_light_frag.glsl",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path);
}

std::shared_ptr<Program> ProgramFactory::loadCubemapProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();

    std::string vertex_path =
        resource_path->GetResourcePath("lighting/cubemap_vert.glsl",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("lighting/cubemap_frag.glsl",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path);
}

std::shared_ptr<Program> ProgramFactory::loadBumpMappingProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();

    std::string vertex_path =
        resource_path->GetResourcePath("lighting/bump_vert.glsl",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("lighting/bump_frag.glsl",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path);
}

std::shared_ptr<Program> ProgramFactory::loadLampProgram() {
    auto resource_path = program_creator_->resource_manager()->resource_path();

    std::string vertex_path =
        resource_path->GetResourcePath("lighting/lamp_vert.glsl",
                                       ifx::ResourceType::SHADER);
    std::string fragment_path =
        resource_path->GetResourcePath("lighting/lamp_frag.glsl",
                                       ifx::ResourceType::SHADER);

    return ProgramLoader(program_creator_).CreateProgram(vertex_path,
                                                         fragment_path);
}
}