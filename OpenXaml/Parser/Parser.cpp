#include "Parser/Parser.h"
#include <string>
#include <fstream>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <vector>
#include "XamlObjects/XamlObject.h"
#include <memory>
#include "XamlObjects/Frame.h"
#include "XamlObjects/Rectangle.h"
#include "XamlObjects/TextBlock.h"
#include "Parser/ErrorReader.h"

using namespace std;
using namespace xercesc;
namespace OpenXaml {
	namespace Parser {
		using namespace OpenXaml;

		Frame ReadFile(string input)
		{
			//http://www.yolinux.com/TUTORIALS/XML-Xerces-C.html
			string fileText;
			ifstream inputStream;
			inputStream.open(input);
			string line;
			while (getline(inputStream, line))
			{
				fileText += line;
			}
			inputStream.close();

			XMLPlatformUtils::Initialize();
			ErrorReader handler;
			XercesDOMParser* parser = new XercesDOMParser();
			parser->setErrorHandler(&handler);
			parser->loadGrammar("../Schema/XamlStandard.xsd", Grammar::SchemaGrammarType);
			parser->setDoSchema(true);
			parser->setValidationScheme(XercesDOMParser::Val_Always);
			parser->setDoNamespaces(true);			
			parser->setIncludeIgnorableWhitespace(false);
			parser->parse(input.c_str());
			
			size_t error = parser->getErrorCount();
			if (error > 0)
			{
				throw 1;
			}
			
			DOMDocument* xmlDoc = parser->getDocument();
			DOMElement* elementRoot = xmlDoc->getDocumentElement();
			const XMLCh *xmlString = elementRoot->getTagName();
			string test = XMLString::transcode(xmlString);
			if (test != "Frame")
			{
				throw 2;
			}

			Frame frame = Frame();			
			frame.LoadFromDOM(elementRoot);
			XMLPlatformUtils::Terminate();
			return frame;
		}		
	}	
}
