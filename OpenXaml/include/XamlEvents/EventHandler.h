#pragma once

#include <vector>
#include <map>
#include "XamlObjects/XamlObject.h"
#include <functional>
namespace OpenXaml
{
	enum class EventType
	{
		ClickEvent
	};

	std::map<EventType, std::vector<XamlObject*>> Events;


	void AddEvent(XamlObject* target, EventType type);

	void RemoveEvent(XamlObject* target, EventType type);

	std::map<std::string, std::function<void(XamlObject*)>> functionMap;
}
