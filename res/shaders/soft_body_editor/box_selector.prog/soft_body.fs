#version 330 core

in vec3 Normal;
in vec3 Tangent;
in vec3 Binormal;
in vec3 FragPos;
in vec2 TexCoords;
in float VertexID;

out vec4 color;

void main() {
	float alpha = 0.5;
	float r = VertexID / 150.0;

	color = vec4(vec3(0,0,0.5), alpha);
}