#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>

namespace xut
{
    namespace xml
    {
        /// A class for handling xerces xml errors and warnings
        class ErrorReader : public xercesc::ErrorHandler
        {
        public:
            void warning(const xercesc::SAXParseException &exc);
            void error(const xercesc::SAXParseException &exc);
            void fatalError(const xercesc::SAXParseException &exc);
            void resetErrors();
        };
    } // namespace xml
} // namespace xut
