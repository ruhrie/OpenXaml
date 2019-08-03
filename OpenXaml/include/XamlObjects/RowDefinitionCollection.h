#pragma once
#include <vector>
#include "XamlObjects/RowDefinition.h"
namespace OpenXaml
{
	class RowDefinitionCollection
	{
	public:
		std::vector<RowDefinition*> Children;
	};
}