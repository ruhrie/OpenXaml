#pragma once
#include "OpenXaml/XamlEvents/XamlEvent.h"
namespace OpenXaml
{
	namespace Events
	{
		///A click event class
		class ClickEvent : public EventBase
		{
		public:
			ClickEvent(double x, double y);
			vec2<float> GetLocation();
		private:
			float xCoord;
			float yCoord;
		};
	}	
}