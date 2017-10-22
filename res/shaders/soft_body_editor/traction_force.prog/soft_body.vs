#version 330 core

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
out float VertexID;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
    vec4 pos4 = vec4(position, 1.0f);
    mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
    gl_Position = pos4;

    // Fragment position is used to
    // calculate the Ray between Fragment and Light position for each fragment
    FragPos = vec3(ModelMatrix * pos4);

    // Multiply by the "Normal Matrix"
    // TODO This should be calculatd on CPU and send as uniform mat4
    mat3 NormalMatrix = mat3(transpose(inverse(ModelMatrix)));
    Normal = normalize(NormalMatrix * normal);
    Tangent = normalize(NormalMatrix * tangent);
    Binormal = normalize(NormalMatrix * binormal);

    TexCoords = texCoords;

	VertexID = gl_VertexID;
}