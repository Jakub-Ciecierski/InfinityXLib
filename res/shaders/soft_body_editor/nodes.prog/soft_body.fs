#version 400 core

out vec4 color;

in vec3 fNormal;

in vec2 fTexCoords;

void main()
{
	color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	if(fTexCoords.x == 10.0){
		color = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}
    
}