#pragma once
#include <vector>
#include "XamlObjects/ColumnDefinition.h"
namespace OpenXaml
{
	class ColumnDefinitionCollection
	{
	public:
		std::vector<ColumnDefinition*> Children;
	};
}