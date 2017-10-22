#version 400 core
#extension GL_ARB_geometry_shader4 : enable

layout (triangles) in;
layout(triangle_strip, max_vertices = 12) out;

in vec2 gTexCoords[3];
out vec2 fTexCoords;

void draw_node(vec4 position, int index){
	float a = 0.015*0.8 * position.z;
	float b = a * 0.75;
	float max = 0.2;
	if(a > max){
		a = max;
	}
	if(gTexCoords[index].x == 10.0f || gTexCoords[index].y == 10.0f){
		a = 2 * a;
		b = 2 * b;
	}

	gl_Position = position + vec4(-b, -a, 0.0, 0.0);
	fTexCoords = gTexCoords[index];
    EmitVertex();

	gl_Position = position + vec4(b, -a, 0.0, 0.0);
	fTexCoords = gTexCoords[index];
    EmitVertex();

	gl_Position = position + vec4(-b, a, 0.0, 0.0);
	fTexCoords = gTexCoords[index];
    EmitVertex();

	gl_Position = position + vec4(b, a, 0.0, 0.0);
	fTexCoords = gTexCoords[index];
    EmitVertex();

    EndPrimitive();
}

void main()
{
	for(int i = 0; i < gl_VerticesIn; i++){
		draw_node(gl_in[i].gl_Position, i);
	}
}
