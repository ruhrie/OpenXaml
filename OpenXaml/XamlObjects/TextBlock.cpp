#include "OpenXaml/XamlObjects/TextBlock.h"
#include "OpenXaml/Environment/Environment.h"
#include "OpenXaml/Environment/Window.h"
#include "OpenXaml/GL/GLConfig.h"
#include "OpenXaml/Properties/Alignment.h"
#include "OpenXaml/Properties/TextWrapping.h"
#include <algorithm>
#include <codecvt>
#include <glad/glad.h>
#include <harfbuzz/hb.h>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <math.h>
using namespace std;
namespace OpenXaml
{
    namespace Objects
    {
        void TextBlock::Draw()
        {
            glBindVertexArray(TextBlock::VAO);
            glUseProgram(GL::xamlShader);
            int vertexColorLocation = glGetUniformLocation(GL::xamlShader, "thecolor");
            int modeLoc = glGetUniformLocation(GL::xamlShader, "mode");
            glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
            glUniform1i(modeLoc, 2);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glBindTexture(GL_TEXTURE_2D, font->getFontAtlasTexture());
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
            glDrawElements(GL_TRIANGLES, 6 * glyphCount, GL_UNSIGNED_SHORT, 0);
        }
        void TextBlock::Initialize()
        {
            glGenVertexArrays(1, &(TextBlock::VAO));
            glBindVertexArray(TextBlock::VAO);
            glGenBuffers(1, &edgeBuffer);
            glGenBuffers(1, &vertexBuffer);
            Update();
        }
        void TextBlock::Update()
        {
            font = Environment::GetFont(FontProperties{FontFamily, FontSize});
            if (font == NULL)
            {
                return;
            }

            vector<size_t> indexes;
            for (size_t i = 0; i < Text.size(); i++)
            {
                char32_t a = Text.at(i);
                if (a == U'\n')
                {
                    indexes.push_back(i);
                }
            }

            float wordWidth = 0; //width of current word
            size_t currentIndex = 0;
            int lineCount = 0; //number of lines
            float width = 0;     //width of current line
            float maxWidth = 0;  //max line width
            size_t charsToRender = 0;
            float fBounds = (maxCoord.x - minCoord.x) / OpenXaml::Environment::window->xScale;
            vector<u32string> splitStrings;
            for (int i = 0; i < indexes.size() + 1; i++)
            {
                size_t index = i == indexes.size() ? Text.size() : indexes.at(i);
                u32string subString = Text.substr(currentIndex, index - currentIndex);
                if (i < indexes.size())
                {
                    currentIndex = indexes.at(i) + 1;
                }
                //we should render this line

                auto formattedText = font->FormatText(subString);
                for (auto character : formattedText)
                {
                    wordWidth += character.xAdvance;
                    if (font->IsSeperator(character.Character))
                    {
                        if (TextWrapping != TextWrapping::NoWrap && width + wordWidth > fBounds)
                        {
                            lineCount++;
                            maxWidth = std::max(maxWidth, width);
                            width = wordWidth;
                            wordWidth = 0;
                        }
                        else
                        {
                            width += wordWidth;
                            wordWidth = 0;
                        }
                    }
                }
                //we now know the number of lines in this 'line' as well as its width, so increment and set the width
                lineCount++;
                maxWidth = std::max(maxWidth, wordWidth);
                charsToRender += formattedText.size();
            }
            maxWidth = std::max(maxWidth, width);
            //we now know the true number of lines and the true width
            //so we can start rendering

            float *vBuffer = (float *)calloc(16 * charsToRender, sizeof(float));
            unsigned short *eBuffer = (unsigned short *)calloc(6 * charsToRender, sizeof(unsigned short));

            wordWidth = 0;
            width = 0;

            int height = (font->Height >> 6);
            float fWidth = maxWidth * OpenXaml::Environment::window->xScale;
            float fHeight = height * OpenXaml::Environment::window->yScale * lineCount;

            switch (VerticalAlignment)
            {
                case VerticalAlignment::Bottom:
                {
                    minRendered.y = minCoord.y;
                    maxRendered.y = min(maxCoord.y, minCoord.y + fHeight);
                    break;
                }
                case VerticalAlignment::Top:
                {
                    maxRendered.y = maxCoord.y;
                    minRendered.y = max(minCoord.y, maxCoord.y - fHeight);
                    break;
                }
                case VerticalAlignment::Center:
                {
                    float mean = 0.5f * (maxCoord.y + minCoord.y);
                    maxRendered.y = min(maxCoord.y, mean + fHeight / 2);
                    minRendered.y = max(minCoord.y, mean - fHeight / 2);
                    break;
                }
                case VerticalAlignment::Stretch:
                {
                    maxRendered.y = maxCoord.y;
                    minRendered.y = minCoord.y;
                    break;
                }
            }

            switch (HorizontalAlignment)
            {
                case HorizontalAlignment::Left:
                {
                    minRendered.x = minCoord.x;
                    maxRendered.x = min(maxCoord.x, minCoord.x + fWidth);
                    break;
                }
                case HorizontalAlignment::Right:
                {
                    maxRendered.x = maxCoord.x;
                    minRendered.x = max(minCoord.x, maxCoord.x - fWidth);
                    break;
                }
                case HorizontalAlignment::Center:
                {
                    float mean = 0.5f * (maxCoord.x + minCoord.x);
                    maxRendered.x = min(maxCoord.x, mean + fWidth / 2);
                    minRendered.x = max(minCoord.x, mean - fWidth / 2);
                    break;
                }
                case HorizontalAlignment::Stretch:
                {
                    maxRendered.x = maxCoord.x;
                    minRendered.x = minCoord.x;
                    break;
                }
            }

            int arrayIndex = 0;
            float penX = 0;
            float penY = maxRendered.y - (height - (font->VerticalOffset >> 6)) * OpenXaml::Environment::window->yScale;
            currentIndex = 0;
            for (int i = 0; i < indexes.size() + 1; i++)
            {
                int priorIndex = 0;
                int ppIndex = 0;
                size_t index = i == indexes.size() ? Text.size() : indexes.at(i);
                u32string subString = Text.substr(currentIndex, index - currentIndex);
                if (i < indexes.size())
                {
                    currentIndex = indexes.at(i) + 1;
                }
                auto formattedText = font->FormatText(subString);
                int k = 0;
                for (auto character : formattedText)
                {
                    wordWidth += character.xAdvance;
                    if (font->IsSeperator(character.Character))
                    {
                        if (TextWrapping != TextWrapping::NoWrap && width + wordWidth > fBounds)
                        {
                            switch (TextAlignment)
                            {
                                case TextAlignment::Center:
                                {
                                    penX = (minRendered.x + maxRendered.x) * 0.5f - width * 0.5f * OpenXaml::Environment::window->xScale;
                                    break;
                                }
                                case TextAlignment::End:
                                {
                                    penX = (maxRendered.x) - width * OpenXaml::Environment::window->xScale;
                                    break;
                                }
                                case TextAlignment::Start:
                                {
                                    penX = minRendered.x;
                                    break;
                                }
                            }

                            for (int j = priorIndex; j < ppIndex + 1; j++)
                            {
                                if (penX > maxCoord.x)
                                {
                                    break;
                                }
                                RenderCharacter(formattedText.at(j), penX, penY, vBuffer, eBuffer, arrayIndex);
                            }

                            priorIndex = ++ppIndex;
                            penY -= height * OpenXaml::Environment::window->yScale;
                            if (penY < minCoord.y - height * OpenXaml::Environment::window->yScale)
                            {
                                break;
                            }
                            width = wordWidth;
                        }
                        else
                        {
                            width += wordWidth;
                        }
                        wordWidth = 0;
                        ppIndex = k;
                    }
                    k++;
                }
                switch (TextAlignment)
                {
                    case TextAlignment::Center:
                    {
                        penX = (minRendered.x + maxRendered.x) * 0.5f - wordWidth * 0.5f * OpenXaml::Environment::window->xScale;
                        break;
                    }
                    case TextAlignment::End:
                    {
                        penX = (maxRendered.x) - width * OpenXaml::Environment::window->xScale;
                        break;
                    }
                    case TextAlignment::Start:
                    {
                        penX = minRendered.x;
                        break;
                    }
                }
                for (int j = priorIndex; j < formattedText.size(); j++)
                {
                    if (penX > maxCoord.x)
                    {
                        break;
                    }
                    RenderCharacter(formattedText.at(j), penX, penY, vBuffer, eBuffer, arrayIndex);
                }
                penY -= height * OpenXaml::Environment::window->yScale;
                width = 0;
            }

            boxWidth = (maxRendered.x - minRendered.x) / OpenXaml::Environment::window->xScale;
            boxHeight = (maxRendered.y - minRendered.y) / OpenXaml::Environment::window->yScale;
            glBindVertexArray(TextBlock::VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * (size_t)arrayIndex * sizeof(unsigned short), eBuffer, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, 16 * (size_t)arrayIndex * sizeof(float), vBuffer, GL_STATIC_DRAW);
            std::free(eBuffer);
            std::free(vBuffer);
            glyphCount = arrayIndex;
        }

        void TextBlock::RenderCharacter(UChar ch, float &penX, float &penY, float *vertexBuffer, unsigned short *edgeBuffer, int &index)
        {
            auto uchar = font->GlyphMap[ch.Character];
            float x0, x1, y0, y1, tx0, tx1, ty0, ty1;
            float dx0, dx1, dy0, dy1;
            dx0 = penX + (ch.xOffset + uchar.xBearingH) * Environment::window->xScale;
            dx1 = dx0 + uchar.width;
            dy1 = penY + (ch.yOffset + uchar.yBearingH) * Environment::window->yScale;
            dy0 = dy1 - uchar.height;

            x0 = max(dx0, minCoord.x);
            x1 = min(dx1, maxCoord.x);
            y0 = min(dy0, maxCoord.y);
            y1 = max(dy1, minCoord.y);

            float dwidth = dx1 - dx0;
            float dheight = dy1 - dy0;
            auto textureLoc = font->GlyphMap[ch.Character];
            if (x0 != dx0)
            {
                tx0 = textureLoc.txMax - (textureLoc.txMax - textureLoc.txMin) * (x1 - x0) / dwidth;
            }
            else
            {
                tx0 = textureLoc.txMin;
            }
            if (x1 != dx1)
            {
                tx1 = textureLoc.txMin + (textureLoc.txMax - textureLoc.txMin) * (x1 - x0) / dwidth;
            }
            else
            {
                tx1 = textureLoc.txMax;
            }
            if (y0 != dy0)
            {
                ty0 = textureLoc.tyMin - (textureLoc.tyMax - textureLoc.tyMin) * (y1 - y0) / dheight;
            }
            else
            {
                ty0 = textureLoc.tyMin;
            }
            if (y1 != dy1)
            {
                ty1 = textureLoc.tyMin + (textureLoc.tyMax - textureLoc.tyMin) * (y1 - y0) / dheight;
            }
            else
            {
                ty1 = textureLoc.tyMax;
            }

            vertexBuffer[16 * index + 0] = x0;
            vertexBuffer[16 * index + 1] = y1;
            vertexBuffer[16 * index + 2] = tx0;
            vertexBuffer[16 * index + 3] = ty1;
            vertexBuffer[16 * index + 4] = x1;
            vertexBuffer[16 * index + 5] = y1;
            vertexBuffer[16 * index + 6] = tx1;
            vertexBuffer[16 * index + 7] = ty1;
            vertexBuffer[16 * index + 8] = x0;
            vertexBuffer[16 * index + 9] = y0;
            vertexBuffer[16 * index + 10] = tx0;
            vertexBuffer[16 * index + 11] = ty0;
            vertexBuffer[16 * index + 12] = x1;
            vertexBuffer[16 * index + 13] = y0;
            vertexBuffer[16 * index + 14] = tx1;
            vertexBuffer[16 * index + 15] = ty0;

            edgeBuffer[6 * index + 0] = 0 + 4 * index;
            edgeBuffer[6 * index + 1] = 1 + 4 * index;
            edgeBuffer[6 * index + 2] = 2 + 4 * index;
            edgeBuffer[6 * index + 3] = 1 + 4 * index;
            edgeBuffer[6 * index + 4] = 2 + 4 * index;
            edgeBuffer[6 * index + 5] = 3 + 4 * index;

            index++;
            penX += ch.xAdvance * OpenXaml::Environment::window->xScale;
            penY -= ch.yAdvance * OpenXaml::Environment::window->yScale;
        }

        TextBlock::TextBlock()
        {
            boxHeight = 0;
            boxWidth = 0;
            edgeBuffer = 0;
            vertexBuffer = 0;
            font = NULL;
        }

        TextBlock::~TextBlock()
        {
            //glBindVertexArray(TextBlock::VAO);
            //glDeleteVertexArrays(1, &TextBlock::VAO);
            XamlObject::~XamlObject();
        }

        void TextBlock::setText(u32string text)
        {
            this->Text = text;
        }
        u32string TextBlock::getText()
        {
            return this->Text;
        }
        void TextBlock::setText(string text)
        {
            std::wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
            this->Text = conv.from_bytes(text);
        }
        void TextBlock::setTextWrapping(OpenXaml::TextWrapping textWrapping)
        {
            this->TextWrapping = textWrapping;
        }
        TextWrapping TextBlock::getTextWrapping()
        {
            return this->TextWrapping;
        }
        void TextBlock::setFontFamily(string family)
        {
            this->FontFamily = family;
        }
        string TextBlock::getFontFamily()
        {
            return this->FontFamily;
        }
        void TextBlock::setFontSize(float size)
        {
            this->FontSize = size;
        }
        float TextBlock::getFontSize()
        {
            return this->FontSize;
        }
        void TextBlock::setFill(unsigned int fill)
        {
            this->Fill = fill;
        }
        unsigned int TextBlock::getFill()
        {
            return this->Fill;
        }
        void TextBlock::setTextAlignment(OpenXaml::TextAlignment alignment)
        {
            this->TextAlignment = alignment;
        }
        TextAlignment TextBlock::getTextAlignment()
        {
            return this->TextAlignment;
        }
        int TextBlock::getWidth()
        {
            return max(this->Width, (int)this->boxWidth);
        }
        int TextBlock::getHeight()
        {
            return max(this->Height, (int)this->boxHeight);
        }
        coordinate TextBlock::getDesiredDimensions()
        {
            if (font == NULL)
            {
                font = Environment::GetFont(FontProperties{FontFamily, FontSize});
            }
            coordinate result = {0, 0};

            vector<size_t> indexes;
            for (size_t i = 0; i < Text.size(); i++)
            {
                char32_t a = Text.at(i);
                if (a == U'\n')
                {
                    indexes.push_back(i);
                }
            }

            float wordWidth = 0; //width of current word
            size_t currentIndex = 0;
            int lineCount = 0; //number of lines
            float width = 0;     //width of current line
            float maxWidth = 0;  //max line width
            size_t charsToRender = 0;
            vector<u32string> splitStrings;
            for (int i = 0; i < indexes.size() + 1; i++)
            {
                size_t index = i == indexes.size() ? Text.size() : indexes.at(i);
                u32string subString = Text.substr(currentIndex, index - currentIndex);
                if (i < indexes.size())
                {
                    currentIndex = indexes.at(i) + 1;
                }
                //we should render this line

                auto formattedText = font->FormatText(subString);
                for (auto character : formattedText)
                {
                    wordWidth += character.xAdvance;
                    if (font->IsSeperator(character.Character))
                    {
                        width += wordWidth;
                        wordWidth = 0;
                    }
                }
                //we now know the number of lines in this 'line' as well as its width, so increment and set the width
                lineCount++;
                maxWidth = std::max(maxWidth, wordWidth);
                charsToRender += formattedText.size();
            }
            maxWidth = std::max(maxWidth, width);

            result.x = std::ceil(maxWidth) * OpenXaml::Environment::window->xScale;
            result.y = lineCount * OpenXaml::Environment::window->yScale * (font->Height >> 6);
            return result;
        }
    } // namespace Objects
} // namespace OpenXaml