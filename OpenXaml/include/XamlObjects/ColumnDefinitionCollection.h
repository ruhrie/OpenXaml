#pragma once
#include <vector>
#include "XamlObjects/ColumnDefinition.h"
namespace OpenXaml
{
	class ColumnDefinitionCollection
	{
	public:
		ColumnDefinitionCollection();
		~ColumnDefinitionCollection();
		std::vector<ColumnDefinition*> Children;
	};
}