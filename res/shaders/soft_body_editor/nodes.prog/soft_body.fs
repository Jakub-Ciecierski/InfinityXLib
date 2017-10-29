#version 400 core

out vec4 color;

in vec3 fNormal;

in vec2 fTexCoords;

void main()
{
	vec4 not_selected_color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	vec4 selected_color = vec4(0.0f, 1.0f, 1.0f, 1.0f);

	color = not_selected_color;
	if(fTexCoords.x > 1.0 || fTexCoords.y > 1.0){
		color = selected_color;
	}
    
}