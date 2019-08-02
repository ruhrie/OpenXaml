#include "XamlObjects/Button.h"
#include "Environment.h"
#include "XamlEvents/XamlEvent.h"
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
		maxRendered = GetMaxRendered();
		minRendered = GetMinRendered();
	}
	Button::Button()
	{
		Label = new TextBlock();
		Frame = new Rectangle();
		DerivedElements.push_back(Label);
		DerivedElements.push_back(Frame);
		AddEvent(XamlEvent::ClickEvent, this);		
	}
	Button::~Button()
	{
		if (OnClick == NULL)
		{
			RemoveEvent(XamlEvent::ClickEvent, this);
		}
		delete Label;
		delete Frame;
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

	void Button::setOnClick(std::function<void(XamlObject*)> func)
	{
		
		if (OnClick != NULL && func == NULL)
		{
			RemoveEvent(XamlEvent::ClickEvent, this);
		}
		else if(OnClick == NULL && func != NULL)
		{
			AddEvent(XamlEvent::ClickEvent, this);
		}
		OnClick = func;
	}

	function<void(XamlObject*)> Button::getOnClick()
	{
		return OnClick;
	}

	void Button::Click()
	{
		if (OnClick != NULL)
		{
			OnClick(this);
		}
	}
	void Button::Click(double x, double y)
	{
		float xc = x * PixelScale.x - 1.0f;
		float yc = 1.0f - y * PixelScale.y;
		if (xc > minRendered.x && xc < maxRendered.x)
		{
			if (yc < maxRendered.y && yc > minRendered.y)
			{
				Click();
			}
		}
	}
}
