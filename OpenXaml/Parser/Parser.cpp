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
#include "XamlObjects/Rectangle.h"
#include <memory>
using namespace std;
using namespace xercesc;
namespace OpenXaml {
	namespace Parser {

		vector<shared_ptr<XamlObject>> getObjects(DOMElement *xml)
		{
			vector<shared_ptr<XamlObject>> result;
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
						shared_ptr<XamlObject> win = make_shared<Frame>();
						Frame *frame = (Frame *)win.get();
						vector<shared_ptr<XamlObject>> childObjects = getObjects(element);
						for (int i = 0; i < childObjects.size(); i++)
						{
							frame->Children.push_back(childObjects[i]);
						}
						result.push_back(win);
					}
					else if (test == "Rectangle")
					{
						shared_ptr<XamlObject> rec = make_shared<Rectangle>();
						Rectangle *rect = (Rectangle *)rec.get();
						vector<shared_ptr<XamlObject>> childObjects = getObjects(element);
						for (int i = 0; i < childObjects.size(); i++)
						{
							rect->Children.push_back(childObjects[i]);
						}
						result.push_back(rec);
					}
					else
					{
						throw 43;
					}
				}
			}
			return result;
		}

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
			vector<shared_ptr<XamlObject>> children = getObjects(elementRoot);

			Frame frame = Frame();
			for (int i = 0; i < children.size(); i++)
			{
				frame.Children.push_back(children[i]);
			}
			
			
			XMLPlatformUtils::Terminate();

			return frame;
		}
		
		
	}	
}
