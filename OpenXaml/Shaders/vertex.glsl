#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 iTexCoord;

uniform vec2 WindowDimensions;

out vec2 texCoord;
void main()
{
	vec2 coordLoc = 2 * position / WindowDimensions - 1;
	texCoord = iTexCoord;
	gl_Position = vec4(coordLoc, 0.0, 1.0);
}