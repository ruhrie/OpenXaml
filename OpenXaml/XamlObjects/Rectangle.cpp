
#include "XamlObjects/XamlObject.h"
#include "XamlObjects/Rectangle.h"
#include <glad/glad.h>

const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";
const GLchar* fragmentSource = R"glsl(
    #version 150 core
    out vec4 outColor;
    void main()
    {
        outColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
)glsl";



GLfloat vertices[] = {
		 0.0f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f
};

void Rectangle::Draw(float xmin, float xmax, float ymin, float ymax)
{
	

	

	
}

Rectangle::Rectangle()
{
	
}