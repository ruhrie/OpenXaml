#version 310 es

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 iTexCoord;

out vec2 texCoord;
void main()
{
	texCoord = iTexCoord;
	gl_Position = vec4(position, 0.0, 1.0);
}