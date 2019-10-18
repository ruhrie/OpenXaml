#pragma once
#include "internal/XamlElement.h"
#include <string>
#include <map>
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
			XamlClass(std::string fileName);
			void WriteToFile(std::string fileName);
		private:
			void AddXamlElement(XamlElement* element);
			std::string RootType;
		};
	}
}