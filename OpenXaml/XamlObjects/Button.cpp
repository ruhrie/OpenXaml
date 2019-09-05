#include "OpenXaml/XamlObjects/Button.h"
#include "OpenXaml/Environment/Environment.h"
#include "OpenXaml/Environment/Window.h"
#include "OpenXaml/XamlEvents/XamlEvent.h"
#include <sstream>

using namespace std;

namespace OpenXaml 
{
	namespace Objects
	{
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
			Label->setText(Text);
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
			Events::AddEvent(Events::XamlEvent::ClickEvent, this);
		}
		Button::~Button()
		{
			if (OnClick == NULL)
			{
				Events::RemoveEvent(Events::XamlEvent::ClickEvent, this);
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
		void Button::setText(std::string content)
		{
			this->Text = content;
		}
		std::string Button::getText()
		{
			return this->Text;
		}

		void Button::setOnClick(std::function<void(XamlObject*)> func)
		{

			if (OnClick != NULL && func == NULL)
			{
				Events::RemoveEvent(Events::XamlEvent::ClickEvent, this);
			}
			else if (OnClick == NULL && func != NULL)
			{
				Events::AddEvent(Events::XamlEvent::ClickEvent, this);
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
			float xc = (float)x * OpenXaml::Environment::window->xScale - 1.0f;
			float yc = 1.0f - (float)y * OpenXaml::Environment::window->yScale;
			if (xc > minRendered.x && xc < maxRendered.x)
			{
				if (yc < maxRendered.y && yc > minRendered.y)
				{
					Click();
				}
			}
		}
	}
}
