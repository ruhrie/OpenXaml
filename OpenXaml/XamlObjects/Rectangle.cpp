#include "OpenXaml/XamlObjects/Rectangle.h"
#include "OpenXaml/Environment/Window.h"
#include "OpenXaml/GL/GLConfig.h"
#include <algorithm>
#include <glad/glad.h>
#include <sstream>
namespace OpenXaml::Objects
{
    void Rectangle::Draw()
    {
        glBindVertexArray(Rectangle::VAO);
        glUseProgram(GL::xamlShader);
        int vertexColorLocation = glGetUniformLocation(GL::xamlShader, "thecolor");
        int modeLoc = glGetUniformLocation(GL::xamlShader, "mode");
        int wUniform = glGetUniformLocation(GL::xamlShader, "WindowDimensions");
        glUniform2f(wUniform, Environment::window->width, Environment::window->height);
        float a;
        float r;
        float g;
        float b;
        a = ((Fill & 0xFF000000) >> 24) / 255.0F;
        r = ((Fill & 0x00FF0000) >> 16) / 255.0F;
        g = ((Fill & 0x0000FF00) >> 8) / 255.0F;
        b = ((Fill & 0x000000FF)) / 255.0F;
        glUniform4f(vertexColorLocation, r, g, b, a);
        glUniform1i(modeLoc, 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
    }

    Rectangle::Rectangle() = default;

    void Rectangle::Initialize()
    {
        glGenVertexArrays(1, &(Rectangle::VAO));
        glBindVertexArray(Rectangle::VAO);
        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &edgeBuffer);
        unsigned short indeces[] =
            {
                0, 1, 2,
                1, 2, 3};
        glBindVertexArray(Rectangle::VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
        glBindVertexArray(0);
        Update();
    }

    void Rectangle::Update()
    {
        XamlObject::Update();
        glBindVertexArray(Rectangle::VAO);

        GLfloat vertices[16];

        if (Rectangle::HorizontalAlignment == HorizontalAlignment::Right)
        {
            vertices[0] = std::max(localMax.x - Width, localMin.x);
            vertices[4] = localMax.x;
            vertices[8] = std::max(localMax.x - Width, localMin.x);
            vertices[12] = localMax.x;
        }
        else if (Rectangle::HorizontalAlignment == HorizontalAlignment::Left)
        {
            vertices[0] = localMin.x;
            vertices[4] = std::min(localMin.x + Width, localMax.x);
            vertices[8] = localMin.x;
            vertices[12] = std::min(localMin.x + Width, localMax.x);
        }
        else if (Rectangle::HorizontalAlignment == HorizontalAlignment::Center)
        {
            float mid = (localMin.x + localMax.x) / 2;
            vertices[0] = std::max(mid - Width / 2, localMin.x);
            vertices[4] = std::min(mid + Width / 2, localMax.x);
            vertices[8] = std::max(mid - Width / 2, localMin.x);
            vertices[12] = std::min(mid + Width / 2, localMax.x);
        }
        else if (Rectangle::HorizontalAlignment == HorizontalAlignment::Stretch)
        {
            if (Width == 0)
            {
                vertices[0] = localMin.x;
                vertices[4] = localMax.x;
                vertices[8] = localMin.x;
                vertices[12] = localMax.x;
            }
            else
            {
                float mid = (localMin.x + localMax.x) / 2;
                vertices[0] = std::min(mid - Width / 2, localMin.x);
                vertices[4] = std::max(mid + Width / 2, localMax.x);
                vertices[8] = std::min(mid - Width / 2, localMin.x);
                vertices[12] = std::max(mid + Width / 2, localMax.x);
            }
        }

        if (Rectangle::VerticalAlignment == VerticalAlignment::Top)
        {
            vertices[1] = localMax.y;
            vertices[5] = localMax.y;
            vertices[9] = std::max(localMax.y - Height, localMin.y);
            vertices[13] = std::max(localMax.y - Height, localMin.y);
        }
        else if (Rectangle::VerticalAlignment == VerticalAlignment::Bottom)
        {
            vertices[1] = std::min(localMin.y + Height, localMax.y);
            vertices[5] = std::min(localMin.y + Height, localMax.y);
            vertices[9] = localMin.y;
            vertices[13] = localMin.y;
        }
        else if (Rectangle::VerticalAlignment == VerticalAlignment::Center)
        {
            float mid = (localMin.y + localMax.y) / 2;
            vertices[1] = mid + Height / 2;
            vertices[5] = mid + Height / 2;
            vertices[9] = mid - Height / 2;
            vertices[13] = mid - Height / 2;
        }
        else if (Rectangle::VerticalAlignment == VerticalAlignment::Stretch)
        {
            if (Height == 0)
            {
                vertices[1] = localMax.y;
                vertices[5] = localMax.y;
                vertices[9] = localMin.y;
                vertices[13] = localMin.y;
            }
            else
            {
                float mid = (localMin.y + localMax.y) / 2;
                vertices[1] = std::min(mid + Height / 2, localMin.y);
                vertices[5] = std::min(mid + Height / 2, localMin.y);
                vertices[9] = std::max(mid - Height / 2, localMax.y);
                vertices[13] = std::max(mid - Height / 2, localMax.y);
            }
        }
        vertices[2] = 0.0F;
        vertices[3] = 1.0F;
        vertices[6] = 1.0F;
        vertices[7] = 1.0F;
        vertices[10] = 0.0F;
        vertices[11] = 0.0F;
        vertices[14] = 1.0F;
        vertices[15] = 0.0F;
        minRendered = {vertices[0], vertices[9]};
        maxRendered = {vertices[4], vertices[1]};
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    }

    Rectangle::~Rectangle()
    {
        glBindVertexArray(Rectangle::VAO);
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &edgeBuffer);
        glDeleteVertexArrays(1, &(Rectangle::VAO));
        XamlObject::~XamlObject();
    }

    void Rectangle::setFill(unsigned int fill)
    {
        this->Fill = fill;
    }
    unsigned int Rectangle::getFill() const
    {
        return this->Fill;
    }
} // namespace OpenXaml::Objects