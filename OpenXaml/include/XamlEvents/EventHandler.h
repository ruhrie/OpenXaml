#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <vector>
#include <map>
#include "XamlObjects/XamlObject.h"
namespace OpenXaml
{
	enum class EventType
	{
		ClickEvent
	};

	std::map<EventType, std::vector<XamlObject*>> Events;


	void AddEvent(XamlObject* target, EventType type);

	void RemoveEvent(XamlObject* target, EventType type);
}


#endif