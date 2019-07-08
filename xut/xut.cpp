#include <cxxopts.hpp>
#include <string>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/dom/DOMText.hpp>
#include "xml/ErrorReader.h"
#include "xml/DomLoader.h"
#include <internal\XamlElement.h>
using namespace std;
using namespace xercesc;
using namespace OpenXaml;

int main(int argc, char* argv[])
{
	std::string inputFile;
	cxxopts::Options options("xut", "xut compiles xaml files into intermediate cpp/h files");
	options.add_options()
		("o,output", "output cpp")
		("i,input", "input xaml", cxxopts::value<std::string>(inputFile))
		("h,header", "header file");

	auto result = options.parse(argc, argv);

	XMLPlatformUtils::Initialize();
	xut::xml::ErrorReader handler;
	XercesDOMParser* parser = new XercesDOMParser();
	parser->setErrorHandler(&handler);
	parser->loadGrammar("../Schema/XamlStandard.xsd", Grammar::SchemaGrammarType);
	parser->setDoSchema(true);
	parser->setValidationScheme(XercesDOMParser::Val_Always);
	parser->setDoNamespaces(true);
	parser->setIncludeIgnorableWhitespace(false);
	parser->parse(inputFile.c_str());

	size_t error = parser->getErrorCount();
	if (error > 0)
	{
		return 1;
	}

	DOMDocument* xmlDoc = parser->getDocument();
	DOMElement* elementRoot = xmlDoc->getDocumentElement();
	const XMLCh* xmlString = elementRoot->getTagName();
	string test = XMLString::transcode(xmlString);

	string fileContents = "";
	XamlElement *n = new XamlElement(elementRoot);
	XamlToString(fileContents, elementRoot);

	XamlObject* root = LoadXaml(elementRoot);

	return 0;
}