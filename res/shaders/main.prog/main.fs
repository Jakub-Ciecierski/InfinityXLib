#version 330 core

/**
 * Contains:
 *
 *  Blinn-Phong
 *
 *  Multiple light sources:
 *      1) Point Light
 *      2) Directional
 *      3) Spotlight
 */

// ---------- IN/OUT ---------- //

in vec3 Normal;
in vec3 Tangent;
in vec3 Binormal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 color;

// ---------- VARIABLES  ---------- //

struct Material {
    sampler2D diffuse; // ambient == diffuse
    sampler2D specular;
    sampler2D normal;

    float shininess;
    float alpha;
};

#define MAX_LIGHT_COUNT 16

struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    mat4 LightSpaceMatrix;

    sampler2D shadow_map;
};

struct SpotLight{
    vec3 position;
    vec3 direction;

    float cutOff;           // cutOff is expected to be the value
    float outerCutOff;      // of cos(_cutOff), where _cutOff comes from CPU

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    mat4 LightSpaceMatrix;
    sampler2D shadow_map;

    float constant;
    float linear;
    float quadratic;
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

// ---------- UNIFORMS ---------- //

uniform PointLight pointLights[MAX_LIGHT_COUNT];
uniform DirLight dirLights[MAX_LIGHT_COUNT];
uniform SpotLight spotLights[MAX_LIGHT_COUNT];

uniform int pointlightCount;
uniform int dirlightCount;
uniform int spotlightCount;

uniform Material material;
uniform vec3 viewPos;

// ---------- HEADERS ---------- //

// Shadow Mapping
float ShadowMappingCalculation(vec4 fragPosLightSpace, sampler2D shadow_map);

vec3 computePointLight(PointLight light, vec3 norm, vec3 fragPos,
                       vec3 viewDir);
vec3 computeDirLight(DirLight light, vec3 norm, vec3 viewDir);
vec3 computeSpotLight(SpotLight light, vec3 norm, vec3 fragPos,
                      vec3 viewDir);

vec3 computeAmbient(vec3 ambientLight);
vec3 computeDiffuse(vec3 norm, vec3 lightDir, vec3 diffuseLight);
vec3 computeSpecular(vec3 norm, vec3 lightDir,
                     vec3 viewDir, vec3 specularLight);
vec3 GetNormal();

float ShadowMappingCalculation(vec4 fragPosLightSpace, sampler2D shadow_map){
    if(textureSize(shadow_map, 0).x <= 1)
        return 0.0;

    // Projection.
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    // Depth map is in range [0,1].
    projCoords = projCoords * 0.5 + 0.5;

    float bias = 0.005;
    float closestDepth = texture(shadow_map, projCoords.xy).r;
    float currentDepth = projCoords.z;

    // PCF. Create softer shadows
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadow_map, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadow_map, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    // A projected coordinate is further than the light's
    // far plane when its z coordinate is larger than 1.0
    if(projCoords.z > 1.0)
        shadow = 0.0;

    // 1 if shadow, 0 otherwise
    return shadow;
}

vec3 computePointLight(PointLight light, vec3 norm, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);

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

vec3 computeDirLight(DirLight light, vec3 norm, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);

    vec3 ambient = computeAmbient(light.ambient);
    vec3 diffuse = computeDiffuse(norm, lightDir, light.diffuse);
    vec3 specular = computeSpecular(norm, lightDir, viewDir, light.specular);

    // Shadow Mapping
    vec4 fragPosLightSpace = light.LightSpaceMatrix * vec4(FragPos, 1.0);
    float shadow = ShadowMappingCalculation(fragPosLightSpace,
                                            light.shadow_map);

    vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular));

    return result;
}

vec3 computeSpotLight(SpotLight light, vec3 norm, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);

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


    vec4 fragPosLightSpace = light.LightSpaceMatrix * vec4(FragPos, 1.0);
    float shadow = ShadowMappingCalculation(fragPosLightSpace,
                                            light.shadow_map);
    vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular));

    //vec3 result = (ambient + diffuse + specular);
    return result;
}


vec3 computeAmbient(vec3 ambientLight){
    vec3 ambientObject = vec3(texture(material.diffuse, TexCoords));
    vec3 ambient = ambientObject * ambientLight;

    return ambient;
}

vec3 computeDiffuse(vec3 norm, vec3 lightDir, vec3 diffuseLight){
    float diffuseFactor = max(dot(norm, lightDir), 0.0f);

    vec3 diffuseObject = vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = diffuseFactor * diffuseObject * diffuseLight;

    return diffuse;
}

vec3 computeSpecular(vec3 norm, vec3 lightDir,
                     vec3 viewDir, vec3 specularLight){
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float specularFactor
        = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    vec3 specularObject = vec3(texture(material.specular, TexCoords));
    vec3 specular = specularObject * specularFactor * specularLight;

    return specular;
}

vec3 GetNormal(){
    return normalize(Normal);
}

void main() {
    vec3 norm = GetNormal();
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0f, 0.0f, 0.0f);

    for(int i = 0; i < pointlightCount; i++){
        result += computePointLight(pointLights[i], norm, FragPos, viewDir);
    }
    for(int i = 0; i < dirlightCount; i++){
        result += computeDirLight(dirLights[i], norm, viewDir);
    }
    for(int i = 0; i < spotlightCount; i++){
        result += computeSpotLight(spotLights[i], norm, FragPos, viewDir);
    }

	color = vec4(result, material.alpha);
}
