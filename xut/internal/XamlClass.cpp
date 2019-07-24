#include "internal/XamlClass.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <Application.h>
#include <xml\ErrorReader.h>

std::string TabOver(std::string input, int number)
{
	std::string result = "";
	for (int i = 0; i < number; i++)
	{
		result += "\t";
	}
	
	std::string tabbed = "\n";
	for (int i = 0; i < number; i++)
	{
		tabbed += "\t";
	}	

	size_t pos = input.find("\n");
	while (pos != std::string::npos)
	{
		input.replace(pos, 1, tabbed);
		pos = input.find("\n", pos + tabbed.size());
	}
	while (input[input.size() - 1] == '\t')
	{
		input.pop_back();
	}
	return result + input;
}

XamlClass::XamlClass(std::string name, XamlElement* element)
{
	Name = name;
	AddXamlElement(element);
}

XamlClass::XamlClass(std::string fileName)
{
	XMLPlatformUtils::Initialize();
	xut::xml::ErrorReader handler;
	XercesDOMParser* parser = new XercesDOMParser();
	parser->setErrorHandler(&handler);
	parser->loadGrammar("../Schema/XamlStandard.xsd", Grammar::SchemaGrammarType);
	parser->setDoSchema(true);
	parser->setValidationScheme(XercesDOMParser::Val_Always);
	parser->setDoNamespaces(true);
	parser->setIncludeIgnorableWhitespace(false);
	parser->parse(fileName.c_str());

	size_t error = parser->getErrorCount();
	if (error > 0)
	{
		throw 1;
	}

	DOMDocument* xmlDoc = parser->getDocument();
	DOMElement* elementRoot = xmlDoc->getDocumentElement();
	const XMLCh* xmlString = elementRoot->getTagName();
	string raw = XMLString::transcode(xmlString);
	if (raw == "Frame")
	{
		XamlElement* n = new XamlElement(elementRoot);
		AddXamlElement(n);
		
	}
	else
	{
		throw 2;
	}
	RootType = raw;
	Name = XMLString::transcode(elementRoot->getAttribute(XMLString::transcode("Class")));
}

void XamlClass::AddXamlElement(XamlElement* element)
{
	if (element->Public)
	{
		PublicInterfaces += element->Initializer;
	}
	else
	{
		PrivateInterfaces += element->Initializer;
	}
	Initializer += element->Body;
	Terminator += element->Terminator;
	for (XamlElement* child : element->Children)
	{
		AddXamlElement(child);
	}
}

void XamlClass::WriteToFile(std::string name)
{
	std::ofstream outputFile;
	outputFile.open(name);
	outputFile << ToString();
	outputFile.close();
}

std::string XamlClass::ToString()
{
	std::string result = "#include <XamlObjects/XamlObjects.h>\n";

	result += "class " + Name + " : public OpenXaml::" + RootType +  "\n";
	result += "{\n";
	
	if (PrivateInterfaces.length() != 0)
	{
		result += "private:\n";
		result += TabOver(PrivateInterfaces, 1);
	}

	result += "public:\n";
	if (PublicInterfaces.length() != 0)
	{
		result += TabOver(PublicInterfaces,1);
	}

	result += "\t" + Name + "()\n\t{\n";
	result += TabOver(Initializer, 2) +"\t}\n";
	
	result += "\t~" + Name + "()\n\t{\n";
	result += TabOver(Terminator, 2) + "\t}\n";
	
	result += "};";

	return result;
}



