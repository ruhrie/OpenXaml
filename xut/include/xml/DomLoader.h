#pragma once
#include <string>
#include <xercesc/dom/DOMElement.hpp>
#include <XamlObjects/XamlObject.h>
#include <XamlObjects/Frame.h>
#include <XamlObjects/Button.h>
#include <XamlObjects/Rectangle.h>
#include <XamlObjects/TextBlock.h>

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