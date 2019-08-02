#pragma once
#include "XamlObjects/ColumnDefinition.h"
#include <vector>
namespace OpenXaml {
	class ColumnDefinitions
	{
	public:
		std::vector<ColumnDefinitions> Columns;
	};
}