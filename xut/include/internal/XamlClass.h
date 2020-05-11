#pragma once
#include "internal/XamlElement.h"
#include <map>
#include <string>
namespace xut
{
    namespace elements
    {
        ///The base object for a xaml file
        class XamlClass
        {
        public:
            std::string FunctionSignitures;
            std::string Name;
            std::string PublicInterfaces = "";
            std::string PrivateInterfaces = "";
            std::string Initializer = "";
            std::string Terminator = "XamlObject::~XamlObject();\n";
            std::string ToString();
            XamlClass(const std::string &fileName);
            void WriteToFile(const std::string &fileName);

        private:
            void AddXamlElement(XamlElement *element);
            std::string RootType;
        };
    } // namespace elements
} // namespace xut