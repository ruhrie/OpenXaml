#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include "XamlObjects/Frame.h"

namespace OpenXaml {
	namespace Parser {
		Frame *ReadFile(std::string inputFile);
		shared_ptr<XamlObject> ParseObject(DOMElement* obj);
	}
}

#endif