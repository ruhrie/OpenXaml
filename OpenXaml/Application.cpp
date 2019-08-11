#include "OpenXaml/Application.h"
#include "OpenXaml/XamlEvents/XamlEvent.h"
#include "OpenXaml/XamlEvents/XamlEvents.h"
#include "OpenXaml/GL/GLConfig.h"
#include "OpenXaml/Environment.h"
#include <glad/glad.h>
#include <filesystem>
#include <iostream>
#ifdef VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>
namespace OpenXaml
{
	GLFWwindow* window;
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			if (action == GLFW_PRESS)
			{
				double x, y;
				glfwGetCursorPos(window, &x, &y);
				Events::ClickEvent* e = new Events::ClickEvent(x, y);
				Events::EventQueue.push_back(e);
			}
		}
	}
	Application::Application()
	{
		
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
		Environment::LoadEnvironment();
	}
	Application::~Application()
	{
		delete frame;
		glfwTerminate();
		Environment::ClearEnvironment();
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
			Events::HandleEvents();
		}
		glfwHideWindow(window);
	}

	void Application::InitializeComponent(Objects::Frame* input)
	{
		frame = input;
		glfwSetWindowSize(window, frame->getWidth(), frame->getHeight());
		frame->setPixelScale(2.0f / frame->getWidth(), 2.0f / frame->getHeight());
		GL::LoadShaders();
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		frame->Initialize();
	}
}