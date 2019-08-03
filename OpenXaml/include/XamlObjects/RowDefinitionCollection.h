#pragma once
#include <vector>
#include "XamlObjects/RowDefinition.h"
namespace OpenXaml
{
	class RowDefinitionCollection
	{
	public:
		RowDefinitionCollection();
		~RowDefinitionCollection();
		std::vector<RowDefinition*> Children;
	};
}