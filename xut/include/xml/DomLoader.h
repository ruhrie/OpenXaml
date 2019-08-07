#pragma once
#include <string>
#include <xercesc/dom/DOMElement.hpp>
#include "OpenXaml/XamlObjects/XamlObject.h"
#include "OpenXaml/XamlObjects/Frame.h"
#include "OpenXaml/XamlObjects/Button.h"
#include "OpenXaml/XamlObjects/Rectangle.h"
#include "OpenXaml/XamlObjects/TextBlock.h""

void XamlToString(std::string &result, xercesc::DOMElement* element);

std::string StringFromFrame(xercesc::DOMElement* element);
std::string StringFromButton(xercesc::DOMElement* element);
std::string StringFromRectangle(xercesc::DOMElement* element);
std::string StringFromTextBlock(xercesc::DOMElement* element);

OpenXaml::XamlObject* LoadXaml(xercesc::DOMElement* element);

OpenXaml::Frame* DomToFrame(xercesc::DOMElement* element);

OpenXaml::Button* DomToButton(xercesc::DOMElement* element);

OpenXaml::Rectangle* DomToRectangle(xercesc::DOMElement* element);

OpenXaml::TextBlock* DomToTextBlock(xercesc::DOMElement* element);