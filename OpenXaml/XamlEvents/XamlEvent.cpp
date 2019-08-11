#include "OpenXaml/XamlEvents/XamlEvent.h"
#include "OpenXaml/XamlEvents/XamlEvents.h"
#include <algorithm>
#include <iostream>
#include "OpenXaml/XamlObjects/Button.h"
namespace OpenXaml
{
	namespace Events
	{
		using namespace Objects;
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
			// reverse the order so the back of the vector is the first entry pushed
			std::reverse(EventQueue.begin(), EventQueue.end());
			// now process in order
			while (EventQueue.size() != 0)
			{
				EventBase* e = EventQueue.back();
				std::set<XamlObject*> targets;
				coordinate location = { 0,0 };
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
				EventQueue.pop_back(); //and remove the processed event
			}
		}
	}
}