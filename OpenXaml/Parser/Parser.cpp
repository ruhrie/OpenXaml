#include "Parser/Parser.h"
#include <string>
#include <fstream>
#include <xercesc/parsers/XercesDOMParser.hpp>

using namespace std;
using namespace xercesc;
namespace OpenXaml {
	namespace Parser {
		string ReadFile(string input)
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


			XercesDOMParser* parser = new XercesDOMParser();
			parser->setValidationScheme(XercesDOMParser::Val_Always);
			parser->setDoNamespaces(true);    // optional

			
			parser->parse(input.c_str());

			DOMDocument* xmlDoc = parser->getDocument();

			DOMElement* elementRoot = xmlDoc->getDocumentElement();


			XMLPlatformUtils::Terminate();

			return fileText;
		}
	}	
}
