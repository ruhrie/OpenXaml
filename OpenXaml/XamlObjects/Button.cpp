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
