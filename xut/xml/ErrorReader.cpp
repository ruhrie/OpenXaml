#include "xml/ErrorReader.h"
#include <string>
#include <iostream>

using namespace std;
using namespace xercesc;

namespace xut
{
    namespace xml
    {
        void ErrorReader::warning(const SAXParseException &exc)
        {
            XMLFileLoc linex = exc.getLineNumber();
            XMLFileLoc colx = exc.getColumnNumber();
            cerr << "Warning: XML Parsing warning on line " << linex << ", column " << colx << ".\n";
            const XMLCh *message = exc.getMessage();
            string test = XMLString::transcode(message);
			cerr << test << "\n";
        }
        void ErrorReader::error(const SAXParseException &exc)
        {
            XMLFileLoc linex = exc.getLineNumber();
            XMLFileLoc colx = exc.getColumnNumber();
            cerr << "Error: XML Parsing exception on line " << linex << ", column " << colx << ".\n";
            const XMLCh *message = exc.getMessage();
            string test = XMLString::transcode(message);
			cerr << test << "\n";
        }
        void ErrorReader::fatalError(const SAXParseException &exc)
        {
            XMLFileLoc linex = exc.getLineNumber();
            XMLFileLoc colx = exc.getColumnNumber();
            cerr << "Error: XML Parsing exception on line " << linex << ", column " << colx << ".\n";
            const XMLCh *message = exc.getMessage();
            string test = XMLString::transcode(message);
            cerr << test << "\n";
        }
        void ErrorReader::resetErrors()
        {

        }
    }
}