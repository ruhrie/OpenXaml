#version 300 es
//This is a mega shader with configuration modes depending on what it is doing
in vec2 texCoord;

uniform vec4 thecolor;
uniform int mode; 
//0 = solid color
//1 = texture
//2 = text
uniform sampler2D inTexture;
void main()
{
	if (mode == 0)
	{
		gl_FragColor = thecolor;
	}		
	else if (mode == 1)
	{
		gl_FragColor = texture(inTexture, texCoord);
	}
	else if (mode == 2)
	{
		vec4 sampled = vec4(1.0, 1.0, 1.0, texture(inTexture, texCoord).x);
		gl_FragColor = sampled * thecolor;
	}
	else
	{
		gl_FragColor = vec4(0,0,0,0);
	}
}