#version 330 core

in vec3 Normal;
in vec3 Tangent;
in vec3 Binormal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 color;

void main() {
	float alpha = 0.3;

	color = vec4(vec3(1,0,0), alpha);
}
