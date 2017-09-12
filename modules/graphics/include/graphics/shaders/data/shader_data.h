#ifndef DUCK_MESH_DATA_H
#define DUCK_MESH_DATA_H

#include <math/math_ifx.h>

#include <string>
#include <vector>

/**
 * Provides all the data used by Meshes and Lights.
 * Provides uniform global strings for shader binding.
 * TODO Separate the Mesh, Light and shader data.
 */

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

    glm::vec3 Tangent;
    glm::vec3 Binormal;
};

struct InstancedData {
    unsigned int data_count;
    std::vector<glm::mat4> model_matrices;
};

extern const std::string MODEL_MATRIX_NAME;
extern const std::string VIEW_MATRIX_NAME;
extern const std::string PROJECTION_MATRIX_NAME;

extern const std::string VIEW_POSITION_NAME;

extern const std::string MATERIAL_AMBIENT_NAME;
extern const std::string MATERIAL_DIFFUSE_NAME;
extern const std::string MATERIAL_SPECULAR_NAME;
extern const std::string MATERIAL_NORMAL_NAME;
extern const std::string MATERIAL_DISPLACEMENT_NAME;
extern const std::string MATERIAL_SHININESS_NAME;
extern const std::string MATERIAL_ALPHA_NAME;

extern const std::string TEXTURE_CUBEMAP_NAME;
// Used in FBO screen rendering
extern const std::string TEXTURE_SCREEN_NAME;

extern const std::string TEXTURE_SHADOW_MAP;
extern const std::string SHADOW_MAP_MODE;

extern const std::string TESSELLATION_LVL_INNER_NAME;
extern const std::string TESSELLATION_LVL_OUTER_NAME;
extern const std::string PATCH_ID_I_NAME;
extern const std::string PATCH_ID_J_NAME;
extern const std::string PATCH_ROW_COUNT_NAME;
extern const std::string PATCH_COLUMN_COUNT_NAME;

/**
 * Light
 */
extern const std::string LIGHT_POINTLIGHT_COUNT;
extern const std::string LIGHT_DIRLIGHT_COUNT;
extern const std::string LIGHT_SPOTLIGHT_COUNT;

extern const std::string LIGHT_SEPARATOR;
extern const std::string LIGHT_SPOTLIGHT_NAME;
extern const std::string LIGHT_POINTLIGHT_NAME;
extern const std::string LIGHT_DIRLIGHT_NAME;

extern const std::string LIGHT_POSITION_NAME;
extern const std::string LIGHT_DIRECTION_NAME;
extern const std::string LIGHT_AMBIENT_NAME;
extern const std::string LIGHT_DIFFUSE_NAME;
extern const std::string LIGHT_SPECULAR_NAME;

extern const std::string LIGHT_SPACE_MATRIX_NAME;

extern const std::string LIGHT_ATTENUATION_CONST_NAME;
extern const std::string LIGHT_ATTENUATION_LINEAR_NAME;
extern const std::string LIGHT_ATTENUATION_QUAD_NAME;

extern const std::string LIGHT_FLASHLIGHT_CUTOFF_NAME;
extern const std::string LIGHT_FLASHLIGHT_OUTER_CUTOFF_NAME;

#endif //DUCK_MESH_DATA_H
