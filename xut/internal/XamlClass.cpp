#include "internal/XamlClass.h"
#include "OpenXaml/Application.h"
#include "Schema/XamlStandard.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xml/ErrorReader.h>

using namespace xercesc;
using namespace std;

namespace xut::elements
{
    std::string TabOver(std::string input, int number)
    {
        std::string result;
        for (int i = 0; i < number; i++)
        {
            result += "\t";
        }

        if (input.empty())
        {
            return result;
        }

        std::string tabbed = "\n";
        for (int i = 0; i < number; i++)
        {
            tabbed += "\t";
        }

        size_t pos = input.find('\n');
        while (pos != std::string::npos)
        {
            input.replace(pos, 1, tabbed);
            pos = input.find('\n', pos + tabbed.size());
        }
        while (input.back() == '\t')
        {
            input.pop_back();
        }
        return result + input;
    }

    XamlClass::XamlClass(const std::string &fileName)
    {
        XMLPlatformUtils::Initialize();
        xut::xml::ErrorReader handler;
        auto *parser = new XercesDOMParser();
        parser->setErrorHandler(&handler);
        parser->setValidationScheme(XercesDOMParser::Val_Always);
        parser->setDoNamespaces(true);
        parser->setDoSchema(true);
        parser->setIncludeIgnorableWhitespace(false);
        parser->cacheGrammarFromParse(true);
        MemBufInputSource schema = xercesc::MemBufInputSource((const XMLByte *)(xut::XamlStandardXSD.c_str()), xut::XamlStandardXSD.size(), "XamlStandard");
        parser->loadGrammar(schema, Grammar::SchemaGrammarType, true);
        parser->useCachedGrammarInParse(true);
        parser->setExternalNoNamespaceSchemaLocation("file:///schema.xsd");
        parser->parse(fileName.c_str());

        size_t error = parser->getErrorCount();
        if (error > 0)
        {
            throw 1;
        }

        DOMDocument *xmlDoc = parser->getDocument();
        DOMElement *elementRoot = xmlDoc->getDocumentElement();
        const XMLCh *xmlString = elementRoot->getTagName();
        string raw = XMLString::transcode(xmlString);
        Name = XMLString::transcode(elementRoot->getAttribute(XMLString::transcode("Class")));
        XamlElement *test = XamlElement::GetXamlElement(elementRoot, true);
        AddXamlElement(test);
        RootType = raw;
    }

    void XamlClass::AddXamlElement(XamlElement *element)
    {
        size_t pos = 0;
        string temp;
        if (element->Public)
        {
            temp = element->Initializer;
            while ((pos = temp.find("%master%", 0)) != std::string::npos)
            {
                temp.replace(pos, 8, Name);
            }
            PublicInterfaces += temp;
        }
        else
        {
            temp = element->Initializer;
            while ((pos = temp.find("%master%", 0)) != std::string::npos)
            {
                temp.replace(pos, 8, Name);
            }
            PrivateInterfaces += temp;
        }
        temp = element->BodyInitializer;
        while ((pos = temp.find("%master%", 0)) != std::string::npos)
        {
            temp.replace(pos, 8, Name);
        }
        Initializer += element->BodyInitializer;
        temp = element->Body;
        while ((pos = temp.find("%master%", 0)) != std::string::npos)
        {
            temp.replace(pos, 8, Name);
        }
        Initializer += temp;
        temp = element->Terminator;
        while ((pos = temp.find("%master%", 0)) != std::string::npos)
        {
            temp.replace(pos, 8, Name);
        }
        Terminator += temp;
        for (XamlElement *child : element->Children)
        {
            AddXamlElement(child);
        }
        temp = element->ChildEnumerator;
        while ((pos = temp.find("%master%", 0)) != std::string::npos)
        {
            temp.replace(pos, 8, Name);
        }
        Initializer += temp;
        temp = element->ExternalFunctions;
        while ((pos = temp.find("%master%", 0)) != std::string::npos)
        {
            temp.replace(pos, 8, Name);
        }
        FunctionSignitures += temp;
    }

    void XamlClass::WriteToFile(const std::string &name)
    {
        std::ofstream outputFile;
        outputFile.open(name);
        outputFile << ToString();
        outputFile.close();
    }

    std::string XamlClass::ToString()
    {
        std::string result = "#include <OpenXaml/XamlObjects/XamlObjects.h>\n#include <functional>\n#include <memory>\n";

        result += "class " + Name + " : public OpenXaml::Objects::" + RootType + "\n";
        result += "{\n";

        if (PrivateInterfaces.length() != 0)
        {
            result += "private:\n";
            result += TabOver(PrivateInterfaces, 1);
        }

        result += "public:\n";
        result += TabOver(FunctionSignitures, 1);
        if (PublicInterfaces.length() != 0)
        {
            result += TabOver(PublicInterfaces, 1);
        }

        result += "\t" + Name + "()\n\t{\n";
        result += TabOver(Initializer, 2) + "\t}\n";

        result += "\t~" + Name + "()\n\t{\n";
        result += TabOver(Terminator, 2) + "\t}\n";

        result += "};";

        return result;
    }
} // namespace xut::elements