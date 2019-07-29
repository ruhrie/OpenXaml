#include "Application.h"
#include "XamlEvents/XamlEvent.h"
#include "XamlEvents/XamlEvents.h"
#include <GL/GLConfig.h>
#include <filesystem>
#include <iostream>
namespace OpenXaml
{
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			if (action == GLFW_PRESS)
			{
				double x, y;
				glfwGetCursorPos(window, &x, &y);
				ClickEvent* e = new ClickEvent(x, y);
				EventQueue.push_back(e);
			}
		}
	}
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
			HandleEvents();
		}
		glfwHideWindow(window);
	}

	void Application::InitializeComponent(Frame* input)
	{
		frame = input;
		glfwSetWindowSize(window, frame->getWidth(), frame->getHeight());
		frame->setPixelScale(2.0f / frame->getWidth(), 2.0f / frame->getHeight());
		GL::LoadShaders();
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		frame->Initialize();
	}
}