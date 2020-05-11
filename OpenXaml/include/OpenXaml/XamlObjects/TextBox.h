#pragma once
#include "OpenXaml/XamlObjects/Rectangle.h"
#include "OpenXaml/XamlObjects/TextBlock.h"
#include "OpenXaml/XamlObjects/XamlObject.h"
namespace OpenXaml
{
    namespace Objects
    {
        ///A TextBox object. Incomplete
        class TextBox : public XamlObject
        {
        public:
            TextBox();
            ~TextBox();
            void Initialize();
            void Draw();
            void Update();
            void setPlaceholderText(const std::string &placeholderText);
            std::string getPlaceholderText();
            void setText(std::string text);
            std::string getText();
            void TextUpdate(const std::string &text);
            void setOnClick(std::function<void(XamlObject *)> func);

        private:
            std::string Text = "";
            std::string PlaceholderText = "Placeholder";
            std::shared_ptr<Rectangle> Frame;
            std::shared_ptr<TextBlock> PlaceholderTextTextBlock;
            std::shared_ptr<TextBlock> TextTextBlock;
            std::shared_ptr<Rectangle> Indicator;
            int Index = 0;
        };
    } // namespace Objects
} // namespace OpenXaml