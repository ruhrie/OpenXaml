#include "OpenXaml/XamlObjects/TextBox.h"

namespace OpenXaml
{
	namespace Objects
	{
		TextBox::TextBox()
		{
			Frame = new Rectangle();
			PlaceholderTextTextBlock = new TextBlock();
			TextTextBlock = new TextBlock();
			TextTextBlock->setText(Text);
			PlaceholderTextTextBlock->setText(PlaceholderText);
		}
		TextBox::~TextBox()
		{
			delete Frame;
			delete PlaceholderTextTextBlock;
			delete TextTextBlock;
		}
		void TextBox::Initialize()
		{
			Frame->Initialize();
			PlaceholderTextTextBlock->Initialize();
			TextTextBlock->Initialize();
			Update();
		}
		void TextBox::Draw()
		{
			Frame->Draw();
			if (Text == "")
			{
				PlaceholderTextTextBlock->Draw();
			}
			else
			{
				TextTextBlock->Draw();
			}
		}
		void TextBox::Update()
		{
			if (Width == 0)
			{
				
			}
			Frame->Update();
			PlaceholderTextTextBlock->Update();
			auto test = PlaceholderTextTextBlock->getDesiredDimensions();
			TextTextBlock->Update();
		}
		void TextBox::setPlaceholderText(std::string placeholderText)
		{
			PlaceholderText = placeholderText;
			PlaceholderTextTextBlock->setText(placeholderText);
		}
		std::string TextBox::getPlaceholderText()
		{
			return PlaceholderText;
		}
		void TextBox::setText(std::string text)
		{
			TextTextBlock->setText(text);
			Text = text;
		}
		std::string TextBox::getText()
		{
			return Text;
		}
	}
}