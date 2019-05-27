#ifndef EVENT_CLICK_H
#define EVENT_CLICK_H
#include <signals.h>
#include "XamlObjects/Coordinate.h"
namespace OpenXaml
{
	class ClickBase
	{
	public:
		void OnClick();
		void CheckClick(coordinate coord) = 0;
	};
}

#endif