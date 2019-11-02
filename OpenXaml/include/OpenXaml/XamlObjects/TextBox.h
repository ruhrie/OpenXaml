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
            void setPlaceholderText(std::string placeholderText);
            std::string getPlaceholderText();
            void setText(std::string text);
            std::string getText();
            void TextUpdate(std::string text);
            void setOnClick(std::function<void(XamlObject *)> func);

        private:
            std::string Text = "";
            std::string PlaceholderText = "Placeholder";
            Rectangle *Frame;
            TextBlock *PlaceholderTextTextBlock;
            TextBlock *TextTextBlock;
            Rectangle *Indicator;
            int Index = 0;
        };
    } // namespace Objects
} // namespace OpenXaml