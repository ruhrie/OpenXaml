#pragma once
#include <string>
#include <xercesc/dom/DOMElement.hpp>
#include "OpenXaml/XamlObjects/XamlObject.h"
#include "OpenXaml/XamlObjects/Frame.h"
#include "OpenXaml/XamlObjects/Button.h"
#include "OpenXaml/XamlObjects/Rectangle.h"
#include "OpenXaml/XamlObjects/TextBlock.h"

namespace xut
{
	void XamlToString(std::string& result, xercesc::DOMElement* element);

	std::string StringFromFrame(xercesc::DOMElement* element);
	std::string StringFromButton(xercesc::DOMElement* element);
	std::string StringFromRectangle(xercesc::DOMElement* element);
	std::string StringFromTextBlock(xercesc::DOMElement* element);

	std::shared_ptr<OpenXaml::Objects::XamlObject> LoadXaml(xercesc::DOMElement* element);

	std::shared_ptr<OpenXaml::Objects::Frame> DomToFrame(xercesc::DOMElement* element);

	std::shared_ptr<OpenXaml::Objects::Button> DomToButton(xercesc::DOMElement* element);

	std::shared_ptr<OpenXaml::Objects::Rectangle> DomToRectangle(xercesc::DOMElement* element);

	std::shared_ptr<OpenXaml::Objects::TextBlock> DomToTextBlock(xercesc::DOMElement* element);
}