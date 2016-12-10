#version 400 core
#extension GL_EXT_gpu_shader4 : enable

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 binormal;

out vec3 Normal;
out vec3 Tangent;
out vec3 Binormal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform sampler2D height_map;

vec3 ComputeNormal();

vec3 ComputeNormal(){
    vec2 size = textureSize2D(height_map, 0);

    float offset_value_x = 1.0 / size.x;
    float offset_value_y = 1.0 / size.y;

    vec3 offset = vec3(offset_value_x, offset_value_y, 0);

    float height = texture(height_map, texCoords).x;
    float height_left = texture(height_map,
                                texCoords - offset.xz).x;
    float height_right = texture(height_map,
                                 texCoords + offset.xz).x;
    float height_down = texture(height_map,
                                texCoords - offset.zy).x;
    float height_up = texture(height_map,
                                texCoords + offset.zy).x;
    vec3 normal = vec3(height_left - height_right,
                       0.01,
                       height_up - height_down);
    return normal;
}

void main()
{
    TexCoords = texCoords;

    float height = texture(height_map, TexCoords ).x;
    vec4 pos4 = vec4(position, 1.0f);

    mat4 translate = mat4(vec4(1, 0, 0, 0.0),
                          vec4(0, 1, 0, 0.0),
                          vec4(0, 0, 1, 0.0),
                          vec4(0.0, height, 0.0, 1));

    mat4 MVP = ProjectionMatrix * ViewMatrix * translate * ModelMatrix;
    gl_Position = MVP * pos4;

    // Fragment position is used to
    // calculate the Ray between Fragment and Light position for each fragment
    FragPos = vec3(translate*ModelMatrix * pos4);

    // Multiply by the "Normal Matrix"
    // TODO This should be calculatd on CPU and send as uniform mat4


    Normal = mat3(transpose(inverse(ModelMatrix))) * normal;
    Tangent = mat3(transpose(inverse(ModelMatrix))) * tangent;
    Binormal = mat3(transpose(inverse(ModelMatrix))) * binormal;

    Normal = ComputeNormal();
}