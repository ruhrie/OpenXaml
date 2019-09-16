#pragma once
#include "OpenXaml/XamlEvents/XamlEvent.h"
namespace OpenXaml
{
	namespace Events
	{
		///A key down event class
		class TextEvent : public EventBase
		{
		public:
			TextEvent(std::string text);
			std::string Text;
		};
	}
}