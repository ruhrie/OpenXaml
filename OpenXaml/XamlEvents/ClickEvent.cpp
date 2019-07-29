#include "XamlEvents/ClickEvent.h"

namespace OpenXaml
{
	ClickEvent::ClickEvent(double x, double y)
	{
		eventType = XamlEvent::ClickEvent;
		xCoord = x;
		yCoord = y;
	}

	coordinate ClickEvent::GetLocation()
	{
		return coordinate{ xCoord, yCoord };
	}
}
