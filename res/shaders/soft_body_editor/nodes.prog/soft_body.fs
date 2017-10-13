#version 400 core

out vec4 color;

in vec3 fNormal;

void main()
{
	if(fNormal.x == 9){
		color = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}else{
		color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	}
    
}