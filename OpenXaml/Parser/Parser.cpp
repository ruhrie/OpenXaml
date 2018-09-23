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
#include "XamlObjects/Frame.h"
using namespace std;
using namespace xercesc;
namespace OpenXaml {
	namespace Parser {

		vector<XamlObject *> getObjects(DOMElement *xml)
		{
			vector<XamlObject *> result;
			DOMNodeList *childNodes = xml->getChildNodes();
			for (int i = 0; i < childNodes->getLength(); i++)
			{
				DOMNode *currentNode = childNodes->item(i);
				if (currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE)
				{
					DOMElement *element = dynamic_cast<DOMElement *>(currentNode);
					const XMLCh *xmlString = element->getTagName();
					string test = XMLString::transcode(xmlString);
					if (test == "Frame")
					{
						Frame win = Frame();
						vector<XamlObject *> childObjects;
						for (int i = 0; i < childObjects.size(); i++)
						{
							win.Children.push_back(childObjects[i]);
						}
						result.push_back(&win);
					}
					else
					{
						throw 43;
					}
				}
			}
			return result;
		}

		Frame * ReadFile(string input)
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
			const XMLCh *xmlString = elementRoot->getTagName();
			string test = XMLString::transcode(xmlString);
			if (test != "Frame")
			{
				throw 2;
			}
			//vector<XamlObject *> result = getObjects(elementRoot);

			Frame *result = &Frame();
			
			
			XMLPlatformUtils::Terminate();

			return result;
		}
		
		
	}	
}
