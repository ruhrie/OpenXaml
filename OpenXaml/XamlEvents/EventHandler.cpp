#include "XamlEvents/EventHandler.h"
#include <algorithm>
#include <iostream>
#include <stdlib.h>
namespace OpenXaml
{
	void AddEvent(XamlObject* target, EventType type)
	{
		Events[type].push_back(target);
	}

	void RemoveEvent(XamlObject* target, EventType type)
	{
		auto index = std::find(Events[type].begin(), Events[type].end(), target);
		if (index != Events[type].end())
		{
			uint64_t dist = std::distance(Events[type].begin(), index);
			std::swap(Events[type].back(), Events[type][dist]);
			Events[type].pop_back();
		}

		else
		{
			std::cerr << "Xaml object not found\n";
		}
	}
}