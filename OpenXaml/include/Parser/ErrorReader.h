#include <xercesc/sax/Errorhandler.hpp>
#include <xercesc/sax/SAXParseException.hpp> 

namespace OpenXaml
{
    namespace Parser
    {
        class ErrorReader : public xercesc::ErrorHandler
        {
        public:
            void warning(const xercesc::SAXParseException &exc);
            void error(const xercesc::SAXParseException &exc);
            void fatalError(const xercesc::SAXParseException &exc);
            void resetErrors();
        };
    }
}
