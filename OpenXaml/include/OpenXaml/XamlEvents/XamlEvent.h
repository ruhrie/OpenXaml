#pragma once
#include <map>
#include <set>
#include <vector>
#include "OpenXaml/XamlObjects/XamlObject.h"
namespace OpenXaml
{
	namespace Events
	{
		///An enumeration of valid xaml events
		enum class XamlEvent
		{
			ClickEvent
		};
		///A class that allows for determining the type of event
		class EventBase
		{
		public:
			XamlEvent eventType;
		};
		extern std::map<XamlEvent, std::set<Objects::XamlObject*>> EventMap; ///A mapping of a xaml event type to the objects currently listening to it
		extern std::vector<EventBase*> EventQueue;/// A queue of events currently waiting to get processed
		void RemoveEvent(XamlEvent event, Objects::XamlObject* target); ///A method to remove an event
		void AddEvent(XamlEvent event, Objects::XamlObject* target); ///A method to add events
		void HandleEvents(); ///A method to process all events that are pending7
	}
}