#include "Application.h"
#include <filesystem>
#include <iostream>
namespace OpenXaml
{
	Environment env = Environment();
	Application::Application()
	{
		FT_Init_FreeType(&(Application::fontLibrary));
		PixelScale = coordinate{ 0,0 };
		frame = NULL;
		if (!glfwInit())
			throw 2;
		glfwWindowHint(GLFW_VISIBLE, 0);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		window = glfwCreateWindow(640, 480, "My Window", NULL, NULL);

		if (!window)
		{
			glfwTerminate();
			throw 2;
		}
		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) /* There was an error initilizing GLAD */
		{
			glfwTerminate();
			throw 2;
		}
		env.Initialize();
	}
	Application::~Application()
	{
		delete frame;
		FT_Done_FreeType(Application::fontLibrary);
		glfwTerminate();
	}

	void Application::Run()
	{
		glfwShowWindow(window);
		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			frame->Draw();
			glfwSwapBuffers(window);

			int width, height;
			glfwGetWindowSize(window, &width, &height);

			glViewport(0, 0, width, height);
			glfwPollEvents();
		}
		glfwHideWindow(window);
	}

	void Application::InitializeComponent()
	{
		throw 2;
	}

	void Application::InitializeComponent(string file)
	{
		frame = OpenXaml::Parser::ReadFile(file);
		glfwSetWindowSize(window, frame->getWidth(), frame->getHeight());
		frame->setPixelScale(2.0f / frame->getWidth(), 2.0f / frame->getHeight());
		GLuint shader = GL::LoadShaders();
		frame->Initialize(shader);
	}
}