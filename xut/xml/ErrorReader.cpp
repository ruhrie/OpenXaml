#include "xml/ErrorReader.h"
#include <iostream>
#include <string>

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
            const XMLCh *message = exc.getMessage();
            string test = XMLString::transcode(message);
            cerr << "Warning: " << test << ", Line: " << linex << ", Column: " << colx << ".\n";
        }
        void ErrorReader::error(const SAXParseException &exc)
        {
            XMLFileLoc linex = exc.getLineNumber();
            XMLFileLoc colx = exc.getColumnNumber();
            const XMLCh *message = exc.getMessage();
            string test = XMLString::transcode(message);
            cerr << "Error: " << test << ", Line: " << linex << ", Column: " << colx << ".\n";
        }
        void ErrorReader::fatalError(const SAXParseException &exc)
        {
            XMLFileLoc linex = exc.getLineNumber();
            XMLFileLoc colx = exc.getColumnNumber();
            const XMLCh *message = exc.getMessage();
            string test = XMLString::transcode(message);
            cerr << "Error: " << test << ", Line: " << linex << ", Column: " << colx << ".\n";
        }
        void ErrorReader::resetErrors()
        {
        }
    } // namespace xml
} // namespace xut