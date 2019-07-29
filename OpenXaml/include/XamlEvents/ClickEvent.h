#pragma once
#include <XamlEvents/XamlEvent.h>
namespace OpenXaml
{
	class ClickEvent : public EventBase
	{
	public:
		ClickEvent(double x, double y);
		coordinate GetLocation();
	private:
		float xCoord;
		float yCoord;
	};
}