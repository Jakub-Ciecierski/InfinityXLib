#version 330 core
#extension GL_EXT_gpu_shader4 : enable

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 binormal;
layout (location = 5) in mat4 instanced_model_matrix;

out vec3 Normal;
out vec3 Tangent;
out vec3 Binormal;
out vec3 FragPos;
out vec2 TexCoords;
flat out int InstanceID;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

// Density of Material box.
uniform int precision_x;
uniform int precision_z;
uniform sampler2D height_map;

float deduce_i_id();
float deduce_j_id();
mat4 ComputeMVP();

float deduce_i_id(){
    return mod(gl_InstanceID, precision_z);
}

float deduce_j_id(){
    float id_f = float(gl_InstanceID);
    float z_f = float(precision_z);
    return floor(id_f/z_f);
}

mat4 ComputeMVP(){
    float height = texelFetch2D(height_map,
                                ivec2(deduce_j_id(), deduce_i_id()),0).x;
    mat4 scale = mat4(vec4(1, 0, 0, 0),
                      vec4(0, height, 0, 0),
                      vec4(0, 0, 1, 0),
                      vec4(0, 0, 0, 1));
    mat4 translate = mat4(vec4(1, 0, 0, 0.0),
                          vec4(0, 1, 0, 0.0),
                          vec4(0, 0, 1, 0.0),
                          vec4(0.0, 0, 0.0, 1));
    mat4 sub_model = translate * scale;
    mat4 model = instanced_model_matrix;
    mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix * model * sub_model;

    return MVP;
}

void main()
{
    InstanceID = gl_InstanceID;

    vec4 pos4 = vec4(position, 1.0f);
    mat4 MVP = ComputeMVP();
    gl_Position = MVP * pos4;

    // Fragment position is used to
    // calculate the Ray between Fragment and Light position for each fragment
    FragPos = vec3(instanced_model_matrix * pos4);

    // Multiply by the "Normal Matrix"
    // TODO This should be calculatd on CPU and send as uniform mat4
    Normal = mat3(transpose(inverse(instanced_model_matrix))) * normal;
    //Tangent = mat3(transpose(inverse(instanced_model_matrix))) * tangent;
    //Binormal = mat3(transpose(inverse(instanced_model_matrix))) * binormal;

    TexCoords = texCoords;
}