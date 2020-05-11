#include "OpenXaml/XamlEvents/XamlEvent.h"
#include "OpenXaml/XamlEvents/XamlEvents.h"
#include "OpenXaml/XamlObjects/Button.h"
#include "OpenXaml/XamlObjects/TextBox.h"
#include <algorithm>
#include <spdlog/spdlog.h>
namespace OpenXaml::Events
{
    using namespace Objects;
    std::map<XamlEvent, std::set<XamlObject *>> EventMap;
    std::vector<EventBase *> EventQueue;
    void RemoveEvent(XamlEvent event, XamlObject *target)
    {
        EventMap[event].erase(target);
    }
    void AddEvent(XamlEvent event, XamlObject *target)
    {
        EventMap[event].insert(target);
    }
    void HandleEvents()
    {
        // reverse the order so the back of the vector is the first entry pushed
        std::reverse(EventQueue.begin(), EventQueue.end());
        // now process in order
        while (!EventQueue.empty())
        {
            EventBase *e = EventQueue.back();
            std::set<XamlObject *> targets;
            vec2<float> location = {0, 0};
            switch (e->eventType)
            {
                case XamlEvent::ClickEvent:
                {
                    auto *c = (ClickEvent *)e;
                    targets = EventMap[XamlEvent::ClickEvent];
                    location = c->GetLocation();

                    for (XamlObject *target : targets)
                    {
                        spdlog::warn("Clicked " + target->getName());
                        target->Click(location.x, location.y);
                    }
                    break;
                }
                case XamlEvent::TextEvent:
                {
                    auto *c = (TextEvent *)e;
                    targets = EventMap[XamlEvent::TextEvent];
                    std::string text = c->Text;
                    for (XamlObject *target : targets)
                    {
                        auto *box = (TextBox *)target;
                        box->TextUpdate(text);
                    }
                    break;
                }
                default:
                {
                    throw 2;
                }
            }
            delete e;
            EventQueue.pop_back(); //and remove the processed event
        }
    }
} // namespace OpenXaml::Events