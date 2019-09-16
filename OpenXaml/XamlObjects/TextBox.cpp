#include "OpenXaml/XamlObjects/TextBox.h"
#include "OpenXaml/Environment/Environment.h"
#include "OpenXaml\Environment\Window.h"
#include "OpenXaml/XamlEvents/XamlEvents.h"
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
			DerivedElements.push_back(PlaceholderTextTextBlock);
			DerivedElements.push_back(TextTextBlock);
			DerivedElements.push_back(Frame);
			Events::AddEvent(Events::XamlEvent::TextEvent, this);
			Events::AddEvent(Events::XamlEvent::ClickEvent, this);
		}
		TextBox::~TextBox()
		{
			Events::RemoveEvent(Events::XamlEvent::TextEvent, this);
			Events::RemoveEvent(Events::XamlEvent::ClickEvent, this);
			delete Frame;
			delete PlaceholderTextTextBlock;
			delete TextTextBlock;
		}

		void TextBox::setOnClick(std::function<void(XamlObject*)> func)
		{
			OnClick = func;
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
			if (Text.empty())
			{
				PlaceholderTextTextBlock->Draw();
			}
			else
			{
				TextTextBlock->setText(Text);
				TextTextBlock->Draw();
			}
		}
		void TextBox::Update()
		{
			auto desiredDimensions = PlaceholderTextTextBlock->getDesiredDimensions();
			if (Width == 0)
			{
				int w = desiredDimensions.x / OpenXaml::Environment::window->xScale;
				Frame->setWidth(w);
				PlaceholderTextTextBlock->setWidth(w);
				TextTextBlock->setWidth(w);
			}
			if (Height == 0)
			{
				int h = desiredDimensions.y / OpenXaml::Environment::window->yScale;
				Frame->setHeight(h);
				PlaceholderTextTextBlock->setHeight(h);
				TextTextBlock->setHeight(h);
			}
			Frame->setFill(0xFFFFFFFF);
			Frame->setHorizontalAlignment(HorizontalAlignment);
			Frame->setVerticalAlignment(VerticalAlignment);
			Frame->Update();
			PlaceholderTextTextBlock->setHorizontalAlignment(HorizontalAlignment);
			PlaceholderTextTextBlock->setVerticalAlignment(VerticalAlignment);
			PlaceholderTextTextBlock->Update();
			TextTextBlock->setHorizontalAlignment(HorizontalAlignment);
			TextTextBlock->setVerticalAlignment(VerticalAlignment);
			TextTextBlock->Update();
			XamlObject::Update();
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

		void TextBox::TextUpdate(std::string text)
		{
			if (Environment::ActiveElement == this)
			{
				Text += text;
			}
		}
	}
}