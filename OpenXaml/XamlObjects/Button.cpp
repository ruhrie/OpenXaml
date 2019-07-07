#include "XamlObjects/Button.h"
#include "Environment.h"
#include "XamlEvents/EventHandler.h"
#include <sstream>
namespace OpenXaml {
	void Button::Draw()
	{
		this->Update();
		Frame->Draw();
		Label->Draw();
	}
	void Button::Initialize()
	{
		Frame->Initialize();
		Label->Initialize();
	}
	void Button::LoadFromDOM(DOMElement* root)
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
		Label->setText(Content);
		Label->setVerticalAlignment(VerticalAlignment);
		Label->setHorizontalAlignment(HorizontalAlignment);
		Label->setTextAlignment(TextAlignment::Center);
		Label->Update();
		Frame->setWidth(Label->getWidth());
		Frame->setHeight(Label->getHeight());
		Frame->setHorizontalAlignment(HorizontalAlignment);
		Frame->setVerticalAlignment(VerticalAlignment);
		Frame->setFill(Fill);
		Frame->Update();
	}
	Button::Button()
	{
		Label = new TextBlock();
		Frame = new Rectangle();
	}
	Button::~Button()
	{
		if (OnClick == NULL)
		{
			//remove event here
		}
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


	void Button::setFill(unsigned int fill)
	{
		this->Fill = fill;
	}
	unsigned int Button::getFill()
	{
		return this->Fill;
	}
	void Button::setContent(string content)
	{
		this->Content = content;
	}
	string Button::getContent()
	{
		return this->Content;
	}

	void Button::setOnClick(function<void(XamlObject*)> func)
	{
		if (OnClick == NULL)
		{
			Events[EventType::ClickEvent].push_back(this);
		}
		OnClick = func;
	}

}
