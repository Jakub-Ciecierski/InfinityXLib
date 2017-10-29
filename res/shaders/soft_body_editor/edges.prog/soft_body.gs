#version 400 core

layout (triangles) in;
layout (line_strip, max_vertices = 4) out;

in vec2 gTexCoords[3];

out vec2 fTexCoords;

void main()
{
	gl_Position = gl_in[0].gl_Position;
	fTexCoords = gTexCoords[0];
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;
	fTexCoords = gTexCoords[1];
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	fTexCoords = gTexCoords[2];
	EmitVertex();

	gl_Position = gl_in[0].gl_Position;
	fTexCoords = gTexCoords[0];
	EmitVertex();

	EndPrimitive();
}