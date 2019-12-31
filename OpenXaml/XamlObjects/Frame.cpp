#include "OpenXaml/XamlObjects/Frame.h"
#include "OpenXaml/Environment/Environment.h"
#include "OpenXaml/Environment/Window.h"
#include "OpenXaml/GL/GLConfig.h"
#include "OpenXaml/XamlObjects/XamlObject.h"
#include <glad/glad.h>
#include <sstream>

namespace OpenXaml
{
    namespace Objects
    {
        Frame::Frame()
        {
            minCoord.x = 0;
            minCoord.y = 0;
            maxCoord.x = Environment::window->width;
            maxCoord.y = Environment::window->height;
            Width = 640;
            Height = 480;
            Fill = 0xFF000000;
            maxRendered = {Environment::window->width, Environment::window->height};
            minRendered = {0,0};
        }

        void Frame::Draw()
        {
            this->Update();
            glBindVertexArray(Frame::VAO);
            glUseProgram(GL::xamlShader);
            int vertexColorLocation = glGetUniformLocation(GL::xamlShader, "thecolor");
            int modeLoc = glGetUniformLocation(GL::xamlShader, "mode");
            int wUniform = glGetUniformLocation(GL::xamlShader, "WindowDimensions");
            glUniform2f(wUniform, Environment::window->width, Environment::window->height);
            float a, r, g, b;
            a = ((Fill & 0xFF000000) >> 24) / 255.0f;
            r = ((Fill & 0x00FF0000) >> 16) / 255.0f;
            g = ((Fill & 0x0000FF00) >> 8) / 255.0f;
            b = ((Fill & 0x000000FF)) / 255.0f;
            glUniform4f(vertexColorLocation, r, g, b, a);
            glUniform1i(modeLoc, 0);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
            for (unsigned int i = 0; i < Children.size(); i++)
            {
                Children[i]->Draw();
            }
        }

        void Frame::Initialize()
        {
            SetBoundingBox({0,0}, {Environment::window->width, Environment::window->height});
            glGenVertexArrays(1, &(Frame::VAO));
            glBindVertexArray(Frame::VAO);
            glGenBuffers(1, &vertexBuffer);
            glGenBuffers(1, &edgeBuffer);
            glBindVertexArray(Frame::VAO);
            float vertices[] = {
                0, 0, 0, 1,
                (float)OpenXaml::Environment::window->width, 0, 1, 1,
                0, (float)OpenXaml::Environment::window->height, 0, 0,
                (float)OpenXaml::Environment::window->width, (float)OpenXaml::Environment::window->height, 1, 0};

            unsigned short indeces[] =
                {
                    0, 1, 2,
                    1, 2, 3};

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);

            Update();

            for (unsigned int i = 0; i < Children.size(); i++)
            {
                Children[i]->Initialize();
            }
        }

        void Frame::Update()
        {
        }

        Frame::~Frame()
        {
            glBindVertexArray(Frame::VAO);
            glDeleteBuffers(1, &vertexBuffer);
            glDeleteBuffers(1, &edgeBuffer);
            glDeleteVertexArrays(1, &VAO);
            XamlObject::~XamlObject();
        }

        void Frame::setFill(unsigned int fill)
        {
            this->Fill = fill;
            this->Update();
        }
        unsigned int Frame::getFill()
        {
            return this->Fill;
        }
    } // namespace Objects
} // namespace OpenXaml
