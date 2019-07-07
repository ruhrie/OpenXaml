#pragma once
#include <xercesc/dom/DOMElement.hpp>
#include <XamlObjects/XamlObject.h>
#include <XamlObjects/Frame.h>
#include <XamlObjects/Button.h>
#include <XamlObjects/Rectangle.h>
#include <XamlObjects/TextBlock.h>

OpenXaml::XamlObject* LoadXaml(xercesc::DOMElement* element);

OpenXaml::Frame* DomToFrame(xercesc::DOMElement* element);

OpenXaml::Button* DomToButton(xercesc::DOMElement* element);

OpenXaml::Rectangle* DomToRectangle(xercesc::DOMElement* element);

OpenXaml::TextBlock* DomToTextBlock(xercesc::DOMElement* element);