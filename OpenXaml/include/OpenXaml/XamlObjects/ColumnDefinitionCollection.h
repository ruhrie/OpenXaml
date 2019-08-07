#pragma once
#include <vector>
#include "OpenXaml/XamlObjects/ColumnDefinition.h"
#include "OpenXaml/XamlObjects/XamlObject.h"
namespace OpenXaml
{
	class ColumnDefinitionCollection : public XamlObject
	{
	public:
		ColumnDefinitionCollection();
		~ColumnDefinitionCollection();
		std::vector<ColumnDefinition*> Children;
		void Draw();
		void Initialize();
		void Update();
	};
}