#pragma once
#include <map>
#include <set>
#include <vector>
#include "OpenXaml/XamlObjects/XamlObject.h"
namespace OpenXaml
{
	enum class XamlEvent
	{
		ClickEvent
	};
	class EventBase
	{
	public:
		XamlEvent eventType;
	};
	extern std::map<XamlEvent, std::set<XamlObject*>> EventMap;
	extern std::vector<EventBase*> EventQueue;
	void RemoveEvent(XamlEvent event, XamlObject* target);
	void AddEvent(XamlEvent event, XamlObject* target);
	void HandleEvents();
}