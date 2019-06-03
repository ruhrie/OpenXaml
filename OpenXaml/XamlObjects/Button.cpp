#include "XamlObjects/Button.h"
#include "Environment.h"
#include "XamlEvents/EventHandler.h"
#include <sstream>
namespace OpenXaml {
	void Button::Draw()
	{
		Frame->Draw();
		Label->Draw();
	}
	void Button::Initialize(GLuint shader)
	{
		Frame->Initialize(shader);
		Label->Initialize(shader);
	}
	void Button::LoadFromDOM(DOMElement *root)
	{
		DOMNamedNodeMap* attributes = root->getAttributes();
		for (int i = 0; i < attributes->getLength(); i++)
		{
			DOMNode* item = attributes->item(i);
			const XMLCh* nameXML = item->getNodeName();
			const XMLCh* valXML = item->getNodeValue();
			string name = XMLString::transcode(nameXML);
			string value = XMLString::transcode(valXML);
			if (name == "Height")
			{
				Button::Height = stoi(value);
			}
			else if (name == "Width")
			{
				Button::Width = stoi(value);
			}
			else if (name == "HorizontalAlignment")
			{
				if (value == "Right")
				{
					Button::HorizontalAlignment = HorizontalAlignment::Right;
				}
				else if (value == "Left")
				{
					Button::HorizontalAlignment = HorizontalAlignment::Left;
				}
				else if (value == "Center")
				{
					Button::HorizontalAlignment = HorizontalAlignment::Center;
				}
				else if (value == "Stretch")
				{
					Button::HorizontalAlignment = HorizontalAlignment::Stretch;
				}
			}
			else if (name == "VerticalAlignment")
			{
				if (value == "Top")
				{
					Button::VerticalAlignment = VerticalAlignment::Top;
				}
				else if (value == "Bottom")
				{
					Button::VerticalAlignment = VerticalAlignment::Bottom;
				}
				else if (value == "Center")
				{
					Button::VerticalAlignment = VerticalAlignment::Center;
				}
				else if (value == "Stretch")
				{
					Button::VerticalAlignment = VerticalAlignment::Stretch;
				}
			}
			else if (name == "Fill")
			{
				std::istringstream iss(value.substr(1, value.size()));
				unsigned int fill;
				iss >> std::hex >> fill;
				Button::Fill = fill;
			}
			else if (name == "Content")
			{
				Button::Content = value;
			}
		}

		auto text = root->getTextContent();
		Button::Text = XMLString::transcode(text);

		Width.onPropertyChanged = std::bind(&Button::Update, this);
		Height.onPropertyChanged = std::bind(&Button::Update, this);
		Text.onPropertyChanged = std::bind(&Button::Update, this);
		Fill.onPropertyChanged = std::bind(&Button::Update, this);

		LoadChildrenFromDOM(root);
		for (int i = 0; i < Children.size(); i++)
		{
			Children[i]->SetBoundingBox(minCoord, maxCoord);
		}
	}
	void Button::Update()
	{
		Frame->setPixelScale(PixelScale);
		Label->setPixelScale(PixelScale);
		Label->Text = Content;
		Label->VerticalAlignment = VerticalAlignment;
		Label->HorizontalAlignment = HorizontalAlignment;
		Label->TextAlignment = TextAlignment::Center;
		Label->Update();		
		Frame->Width = Label->GetWidth();
		Frame->Height = Label->GetHeight();
		Frame->HorizontalAlignment = HorizontalAlignment;
		Frame->VerticalAlignment = VerticalAlignment;
		Frame->Fill = Fill;
		Frame->Update();
	}
	Button::Button()
	{
		Label = new TextBlock();
		Frame = new Rectangle();
	}
	Button::~Button()
	{
		delete Label;
		delete Frame;
	}
	void Button::SetBoundingBox(coordinate min, coordinate max)
	{
		minCoord = min;
		maxCoord = max;
		Frame->SetBoundingBox(min, max);
		Label->SetBoundingBox(min, max);
	}
}