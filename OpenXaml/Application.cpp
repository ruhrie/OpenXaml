#include "OpenXaml/Application.h"
#include "OpenXaml/Animation/Animation.h"
#include "OpenXaml/Environment/Environment.h"
#include "OpenXaml/Environment/Window.h"
#include "OpenXaml/GL/GLConfig.h"
#include "OpenXaml/XamlEvents/XamlEvent.h"
#include "OpenXaml/XamlEvents/XamlEvents.h"
#include <codecvt>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
namespace OpenXaml
{
    GLFWwindow *window;
    void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
        {
            if (action == GLFW_PRESS)
            {
                double x, y;
                glfwGetCursorPos(window, &x, &y);
                Events::ClickEvent *e = new Events::ClickEvent(x, y);
                Events::EventQueue.push_back(e);
            }
        }
    }

    void windowSizeCallback(GLFWwindow *window, int width, int height)
    {
        Environment::UpdateWindow();
        Environment::window->width = width;
        Environment::window->height = height;
    }

    void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
    }

    void textCallback(GLFWwindow *window, unsigned int codepoint)
    {
        char32_t unicodeInput = (char32_t)codepoint;
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        std::string text = converter.to_bytes(unicodeInput);
        Events::TextEvent *e = new Events::TextEvent(text);
        Events::EventQueue.push_back(e);
    }

    Application::Application()
    {
        PixelScale = {0.0f, 0.0f};
        Environment::window = new Environment::Window();
        frame = NULL;
        if (!glfwInit())
            throw 2;
        glfwWindowHint(GLFW_VISIBLE, 0);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        window = glfwCreateWindow(640, 480, "My Window", NULL, NULL);
        Environment::window->width = 640;
        Environment::window->height = 480;
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
        Animation::StartAnimationThread();
    }
    Application::~Application()
    {
        Animation::StopAnimationThread();
        delete frame;
        glfwTerminate();
        Environment::ClearEnvironment();
    }

    void Application::Run()
    {
        glfwSwapInterval(1);
        glfwShowWindow(window);
        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            frame->Draw();
            glfwSwapBuffers(window);

            int width, height;
            glfwGetWindowSize(window, &width, &height);

            glViewport(0, 0, width, height);
            glfwWaitEvents();
            Events::HandleEvents();
        }
        glfwHideWindow(window);
    }

    void Application::InitializeComponent(Objects::Frame *input)
    {
        frame = input;
        glfwSetWindowSize(window, frame->getWidth(), frame->getHeight());
        Environment::window->width = frame->getWidth();
        Environment::window->height = frame->getHeight();
        GL::LoadShaders();
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetKeyCallback(window, keyCallback);
        glfwSetCharCallback(window, textCallback);
        glfwSetWindowSizeCallback(window, windowSizeCallback);
        frame->Initialize();
    }
} // namespace OpenXaml