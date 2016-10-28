#version 330 core
#extension GL_EXT_gpu_shader4 : enable

/**
 * Contains:
 *
 *  Blinn-Phong
 *
 *  Multiple light sources:
 *      1) Point Light
 *      2) Directional
 *      3) Spotlight
 *
 *  Bump Mapping (TODO Correct TBN)
 */

// ---------- IN/OUT ---------- //

in vec3 Normal;
in vec3 Tangent;
in vec3 Binormal;
in vec3 FragPos;
in vec2 TexCoords;
// just use x
flat in int InstanceID;

out vec4 color;

// ---------- VARIABLES  ---------- //

struct Material {
    sampler2D diffuse; // ambient == diffuse
    sampler2D specular;
    sampler2D normal;

    float shininess;
};

#define MAX_LIGHT_COUNT 16

struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    mat4 LightSpaceMatrix;
};

struct PointLight{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight{
    vec3 position;
    vec3 direction;

    float cutOff;           // cutOff is expected to be the value
    float outerCutOff;      // of cos(_cutOff), where _cutOff comes from CPU

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

// Shadow Mapping
uniform sampler2D shadow_map;

// ---------- UNIFORMS ---------- //

uniform PointLight pointLights[MAX_LIGHT_COUNT];
uniform DirLight dirLights[MAX_LIGHT_COUNT];
uniform SpotLight spotLights[MAX_LIGHT_COUNT];

uniform int pointlightCount;
uniform int dirlightCount;
uniform int spotlightCount;

uniform Material material;
uniform vec3 viewPos;

// Density of Material box.
uniform int precision_x;
uniform int precision_z;

uniform sampler2D height_map;

// ---------- HEADERS ---------- //

// Shadow Mapping
float ShadowMappingCalculation(vec4 fragPosLightSpace);

vec3 computePointLight(PointLight light, vec3 norm, vec3 fragPos,
                       vec3 viewDir, mat3 TBN);
vec3 computeDirLight(DirLight light, vec3 norm, vec3 viewDir, mat3 TBN);
vec3 computeSpotLight(SpotLight light, vec3 norm, vec3 fragPos,
                      vec3 viewDir, mat3 TBN);

vec3 computeAmbient(vec3 ambientLight);
vec3 computeDiffuse(vec3 norm, vec3 lightDir, vec3 diffuseLight);
vec3 computeSpecular(vec3 norm, vec3 lightDir,
                     vec3 viewDir, vec3 specularLight);

vec2 GetMappedTexCoords();
float deduce_i_id();
float deduce_j_id();

float ShadowMappingCalculation(vec4 fragPosLightSpace){
    // Projection.
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    // Depth map is in range [0,1].
    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(shadow_map, projCoords.xy).r;
    float currentDepth = projCoords.z;
    float shadow = closestDepth < currentDepth ? 1 : 0;

    //return currentDepth;
    //return closestDepth;
    return shadow;
}

vec3 computePointLight(PointLight light, vec3 norm, vec3 fragPos,
                        vec3 viewDir, mat3 TBN){
    vec3 lightDir = normalize(light.position - fragPos);

    // ---- Transform to TBN basis ----- //
    //viewDir = TBN * viewDir;
    //lightDir = TBN * lightDir;

    vec3 ambient = computeAmbient(light.ambient);
    vec3 diffuse = computeDiffuse(norm, lightDir, light.diffuse);
    vec3 specular = computeSpecular(norm, lightDir, viewDir, light.specular);

    // ---- Attenuation ----- //
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f /
    ((light.constant) + (light.linear * distance) +
    (light.quadratic * (distance* distance)));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = (ambient + diffuse + specular);

    return result;
}

vec3 computeDirLight(DirLight light, vec3 norm, vec3 viewDir, mat3 TBN){
    vec3 lightDir = normalize(-light.direction);

    // ---- Transform to TBN basis ----- //
    //viewDir = TBN * viewDir;
    //lightDir = TBN * lightDir;

    vec3 ambient = computeAmbient(light.ambient);
    vec3 diffuse = computeDiffuse(norm, lightDir, light.diffuse);
    vec3 specular = computeSpecular(norm, lightDir, viewDir, light.specular);

    vec3 result = (ambient + diffuse + specular);

    return result;
}

vec3 computeSpotLight(SpotLight light, vec3 norm, vec3 fragPos, vec3 viewDir,
                      mat3 TBN){
    vec3 lightDir = normalize(light.position - fragPos);

    // ---- Transform to TBN basis ----- //
    //viewDir = TBN * viewDir;
    //lightDir = TBN * lightDir;

    vec3 ambient = computeAmbient(light.ambient);
    vec3 diffuse = computeDiffuse(norm, lightDir, light.diffuse);
    vec3 specular = computeSpecular(norm, lightDir, viewDir, light.specular);

    // ---- Spotlight ----- //
    // Check the flashlight condition.
    // The cosine between light direction and direction from the fragment
    float theta = dot(lightDir, normalize(-light.direction));
    // Calculate the outer cone difference
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // ---- Attenuation ----- //
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f /  ((light.constant) + (light.linear * distance) +
        (light.quadratic * (distance* distance)));

    ambient *= attenuation;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    vec3 result = (ambient + diffuse + specular);
    return result;
}


vec3 computeAmbient(vec3 ambientLight){
    vec2 mapped_tex_coords = GetMappedTexCoords();

    vec3 ambientObject = vec3(texture(material.diffuse, mapped_tex_coords));
    vec3 ambient = ambientObject * ambientLight;

    return ambient;
}

vec3 computeDiffuse(vec3 norm, vec3 lightDir, vec3 diffuseLight){
    vec2 mapped_tex_coords = GetMappedTexCoords();

    float diffuseFactor = max(dot(norm, lightDir), 0.0f);

    vec3 diffuseObject = vec3(texture(material.diffuse, mapped_tex_coords));
    vec3 diffuse = diffuseFactor * diffuseObject * diffuseLight;

    return diffuse;
}

vec3 computeSpecular(vec3 norm, vec3 lightDir,
                     vec3 viewDir, vec3 specularLight){
    vec2 mapped_tex_coords = GetMappedTexCoords();

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float specularFactor
        = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    vec3 specularObject = vec3(texture(material.specular, mapped_tex_coords));
    vec3 specular = specularObject * specularFactor * specularLight;

    return specular;
}

vec2 GetMappedTexCoords(){
    float i = deduce_i_id();
    float j = deduce_j_id();

    float u = TexCoords.x;
    float v = TexCoords.y;

    float minJ = j / precision_x;
    float maxJ = (j + 1) / precision_x;
    float rJ = maxJ - minJ;

    float minI = i / precision_z;
    float maxI = (i + 1) / precision_z;
    float rI = maxI - minI;

    //return vec2(rJ * u + minJ, rI * v + minI);
    return vec2(rI * v + minI,
                rJ * u + minJ);
}

float deduce_i_id(){
    return mod(InstanceID, precision_z);
}

float deduce_j_id(){
    float id_f = float(InstanceID);
    float z_f = float(precision_z);
    return floor(id_f/z_f);
}

void main() {
    // Load normal from normal map and normalize to [-1. 1].
    vec3 norm = normalize(texture(material.normal, TexCoords).rgb * 2.0 - 1.0);
    norm = normalize(Normal);

    vec3 viewDir = normalize(viewPos - FragPos);

    // The Tangent Basis
    mat3 TBN = transpose(mat3(Tangent, Binormal, Normal));

    vec3 result = vec3(0.0f, 0.0f, 0.0f);

    for(int i = 0; i < pointlightCount; i++){
        result += computePointLight(pointLights[i], norm, FragPos, viewDir,
                                    TBN);
    }
    for(int i = 0; i < dirlightCount; i++){
        result += computeDirLight(dirLights[i], norm, viewDir, TBN);
    }
    for(int i = 0; i < spotlightCount; i++){
        result += computeSpotLight(spotLights[i], norm, FragPos, viewDir, TBN);
    }

    color = vec4(result, 1.0f);

    float i = deduce_j_id() / 281;

    vec2 height_map_coords = vec2(deduce_j_id() / 15.0,
                                  deduce_i_id() / 15.0);

    vec4 v = texelFetch2D(height_map,
                     ivec2(deduce_j_id(), deduce_i_id()),0);
/*
    vec4 v = texelFetch2D(height_map,
                          ivec2(0,10),0);*/
    //color = vec4(i, 0, 0, 1);
    //color = vec4(i, i, i, 1);
    //color = vec4(v.x, 0, 0, 1);



    //float depthValue = texture(shadow_map, TexCoords).r;
    //color = vec4(vec3(depthValue), 1.0);
}