#version 400 core

layout (triangles) in;
layout(triangle_strip, max_vertices = 12) out;

in vec3 vColor[];
out vec3 fColor;

void draw_node(vec4 position){
	float a = 0.015*0.5 * position.z;
	float b = a * 0.75;
	float max = 0.2;
	if(a > max){
		a = max;
	}

	gl_Position = position + vec4(-b, -a, 0.0, 0.0);
    EmitVertex();

	gl_Position = position + vec4(b, -a, 0.0, 0.0);
    EmitVertex();

	gl_Position = position + vec4(-b, a, 0.0, 0.0);
    EmitVertex();

	gl_Position = position + vec4(b, a, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}

void main()
{
	draw_node(gl_in[0].gl_Position);
	draw_node(gl_in[1].gl_Position);
	draw_node(gl_in[2].gl_Position);
}
