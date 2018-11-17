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
using namespace std;
using namespace xercesc;
namespace OpenXaml {
	namespace Parser {
		using namespace OpenXaml;
		vector<shared_ptr<XamlObject>> getObjects(DOMElement *xml)
		{
			vector<shared_ptr<XamlObject>> result;
			DOMNodeList *childNodes = xml->getChildNodes();
			for (unsigned int i = 0; i < childNodes->getLength(); i++)
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
						frame->GetAttributes(element);
						vector<shared_ptr<XamlObject>> childObjects = getObjects(element);
						for (unsigned int i = 0; i < childObjects.size(); i++)
						{
							frame->Children.push_back(childObjects[i]);
						}
						result.push_back(win);
					}
					else if (test == "Rectangle")
					{
						shared_ptr<XamlObject> rec = make_shared<OpenXaml::Rectangle>();
						OpenXaml::Rectangle *rect = (OpenXaml::Rectangle *)rec.get();
						rect->GetAttributes(element);
						vector<shared_ptr<XamlObject>> childObjects = getObjects(element);
						for (unsigned int i = 0; i < childObjects.size(); i++)
						{
							rect->Children.push_back(childObjects[i]);
						}
						result.push_back(rec);
					}
					else if (test == "TextBlock")
					{
						shared_ptr<XamlObject> rec = make_shared<OpenXaml::TextBlock>();
						OpenXaml::TextBlock *rect = (OpenXaml::TextBlock *)rec.get();
						rect->GetAttributes(element);
						vector<shared_ptr<XamlObject>> childObjects = getObjects(element);
						for (unsigned int i = 0; i < childObjects.size(); i++)
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
			parser->loadGrammar("../Schema/XamlStandard.xsd", Grammar::SchemaGrammarType);
			//parser->setExternalSchemaLocation("../Schema/XamlStandard.xsd"); //using this causes an error, and I can't get the error handler to properly execute
			//Will need fixing before release
			parser->setDoSchema(true);
			parser->setValidationScheme(XercesDOMParser::Val_Always);
			parser->setDoNamespaces(true);			
			parser->setIncludeIgnorableWhitespace(false);
			parser->parse(input.c_str());


			
			size_t error = parser->getErrorCount();

			if (error != 0)
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

			vector<shared_ptr<XamlObject>> children = getObjects(elementRoot);
			shared_ptr<XamlObject> obj = XamlObject::ParseObject(elementRoot);
			
			//auto testa = ParseObject(elementRoot);
			Frame frame = Frame();
			//frame->LoadFromDOM(elementRoot);
			Frame asdf = Frame();
			
			asdf.LoadFromDOM(elementRoot);
			XMLPlatformUtils::Terminate();
			return asdf;
			frame.GetAttributes(elementRoot);
			for (unsigned int i = 0; i < children.size(); i++)
			{
				frame.Children.push_back(children[i]);
			}
			
			return frame;
			XMLPlatformUtils::Terminate();
			
			return *(Frame*)obj.get();
		}
		
		
	}	
}
