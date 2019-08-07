#include "OpenXaml/XamlEvents/XamlEvent.h"
#include "OpenXaml/XamlEvents/XamlEvents.h"
#include <algorithm>
#include <iostream>
#include "OpenXaml/XamlObjects/Button.h"
namespace OpenXaml
{
	std::map<XamlEvent, std::set<XamlObject*>> EventMap;
	std::vector<EventBase*> EventQueue;
	void RemoveEvent(XamlEvent event, XamlObject* target)
	{
		EventMap[event].erase(target);
	}
	void AddEvent(XamlEvent event, XamlObject* target)
	{
		EventMap[event].insert(target);
	}
	void HandleEvents()
	{
		std::reverse(EventQueue.begin(), EventQueue.end());
		while (EventQueue.size() != 0)
		{
			EventBase* e = EventQueue.back();
			std::set<XamlObject*> targets;
			coordinate location;
			switch (e->eventType)
			{
			case XamlEvent::ClickEvent:
			{
				ClickEvent* c = (ClickEvent*)e;
				targets = EventMap[XamlEvent::ClickEvent];
				location = c->GetLocation();
				break;
			}
			}

			for (XamlObject* target : targets)
			{
				Button* b = (Button*)target;
				b->Click(location.x, location.y);
			}
			delete e;
			EventQueue.pop_back();
		}
	}
}