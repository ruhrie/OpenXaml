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
#include <math.h>
#include <sstream>
#include <string>
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
            XamlObject::Update();
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
            int lineCount = 0;  //number of lines
            float width = 0;    //width of current line
            float maxWidth = 0; //max line width
            size_t charsToRender = 0;
            float fBounds = (localMax.x - localMin.x);
            vector<u32string> splitStrings;
            for (uint32_t i = 0; i < indexes.size() + 1; i++)
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
            float fWidth = maxWidth;
            float fHeight = height * lineCount;

            switch (VerticalAlignment)
            {
                case VerticalAlignment::Bottom:
                {
                    minRendered.y = localMin.y;
                    maxRendered.y = min(localMax.y, localMin.y + fHeight);
                    break;
                }
                case VerticalAlignment::Top:
                {
                    maxRendered.y = localMax.y;
                    minRendered.y = max(localMin.y, localMax.y - fHeight);
                    break;
                }
                case VerticalAlignment::Center:
                {
                    float mean = 0.5f * (localMax.y + localMin.y);
                    maxRendered.y = min(localMax.y, mean + fHeight / 2);
                    minRendered.y = max(localMin.y, mean - fHeight / 2);
                    break;
                }
                case VerticalAlignment::Stretch:
                {
                    maxRendered.y = localMax.y;
                    minRendered.y = localMin.y;
                    break;
                }
            }

            switch (HorizontalAlignment)
            {
                case HorizontalAlignment::Left:
                {
                    minRendered.x = localMin.x;
                    maxRendered.x = min(localMax.x, localMin.x + fWidth);
                    break;
                }
                case HorizontalAlignment::Right:
                {
                    maxRendered.x = localMax.x;
                    minRendered.x = max(localMin.x, localMax.x - fWidth);
                    break;
                }
                case HorizontalAlignment::Center:
                {
                    float mean = 0.5f * (localMax.x + localMin.x);
                    maxRendered.x = min(localMax.x, mean + fWidth / 2);
                    minRendered.x = max(localMin.x, mean - fWidth / 2);
                    break;
                }
                case HorizontalAlignment::Stretch:
                {
                    maxRendered.x = localMax.x;
                    minRendered.x = localMin.x;
                    break;
                }
            }

            int arrayIndex = 0;
            float penX = minRendered.x;
            float penY = maxRendered.y - (height - (font->VerticalOffset >> 6));
            currentIndex = 0;
            for (uint32_t i = 0; i < indexes.size() + 1; i++)
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
                                    penX = (minRendered.x + maxRendered.x) * 0.5f - width * 0.5f;
                                    break;
                                }
                                case TextAlignment::End:
                                {
                                    penX = (maxRendered.x) - width;
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
                                if (penX > localMax.x)
                                {
                                    break;
                                }
                                RenderCharacter(formattedText.at(j), penX, penY, vBuffer, eBuffer, arrayIndex);
                            }

                            priorIndex = ++ppIndex;
                            penY -= height;
                            if (penY < localMin.y - height)
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
                        penX = (minRendered.x + maxRendered.x) * 0.5f - wordWidth * 0.5f;
                        break;
                    }
                    case TextAlignment::End:
                    {
                        penX = (maxRendered.x) - width;
                        break;
                    }
                    case TextAlignment::Start:
                    {
                        penX = minRendered.x;
                        break;
                    }
                }
                for (uint32_t j = priorIndex; j < formattedText.size(); j++)
                {
                    if (penX > localMax.x)
                    {
                        break;
                    }
                    RenderCharacter(formattedText.at(j), penX, penY, vBuffer, eBuffer, arrayIndex);
                }
                penY -= height;
                width = 0;
            }

            boxWidth = (maxRendered.x - minRendered.x);
            boxHeight = (maxRendered.y - minRendered.y);
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
            dx0 = penX + (ch.xOffset + uchar.xBearingH);
            dx1 = dx0 + uchar.width;
            dy1 = penY + (ch.yOffset + uchar.yBearingH);
            dy0 = dy1 - uchar.height;

            x0 = clamp(dx0, localMin.x, localMax.x);
            x1 = clamp(dx1, localMin.x, localMax.x);
            y0 = clamp(dy0, localMin.y, localMax.y);
            y1 = clamp(dy1, localMin.y, localMax.y);

            float dwidth = dx1 - dx0;
            float dheight = dy1 - dy0;
            auto textureLoc = font->GlyphMap[ch.Character];
            //handle the font textures, note that they are upside down
            if (x0 != dx0)
            {
                //we are missing part of the left
                tx0 = textureLoc.txMax - (textureLoc.txMax - textureLoc.txMin) * (x1 - x0) / dwidth;
            }
            else
            {
                tx0 = textureLoc.txMin;
            }
            if (x1 != dx1)
            {
                //we are missing part of the right
                tx1 = textureLoc.txMin + (textureLoc.txMax - textureLoc.txMin) * (x1 - x0) / dwidth;
            }
            else
            {
                tx1 = textureLoc.txMax;
            }
            if (y0 != dy0)
            {
                //we are missing part of the bottom
                ty0 = textureLoc.tyMax - (textureLoc.tyMax - textureLoc.tyMin) * (y1 - y0) / dheight;
            }
            else
            {
                ty0 = textureLoc.tyMin;
            }
            if (y1 != dy1)
            {
                //we are missing part of the bottom
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
            penX += ch.xAdvance;
            penY -= ch.yAdvance;
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
            return std::ceil(max(this->Width, this->boxWidth));
        }
        int TextBlock::getHeight()
        {
            return std::ceil(max(this->Height, this->boxHeight));
        }
        vec2<float> TextBlock::getDesiredDimensions()
        {
            if (font == NULL)
            {
                font = Environment::GetFont(FontProperties{FontFamily, FontSize});
            }
            vec2<float> result = {0, 0};

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
            int lineCount = 0;  //number of lines
            float width = 0;    //width of current line
            float maxWidth = 0; //max line width
            size_t charsToRender = 0;
            vector<u32string> splitStrings;
            for (uint32_t i = 0; i < indexes.size() + 1; i++)
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

            result.x = std::ceil(maxWidth);
            result.y = lineCount * (font->Height >> 6);
            return result;
        }
    } // namespace Objects
} // namespace OpenXaml