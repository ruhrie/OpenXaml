#include "OpenXaml/XamlEvents/ClickEvent.h"

namespace OpenXaml
{
	namespace Events
	{
		ClickEvent::ClickEvent(double x, double y)
		{
			eventType = XamlEvent::ClickEvent;
			xCoord = (float)x;
			yCoord = (float)y;
		}

		coordinate ClickEvent::GetLocation()
		{
			return coordinate{ xCoord, yCoord };
		}
	}
}
