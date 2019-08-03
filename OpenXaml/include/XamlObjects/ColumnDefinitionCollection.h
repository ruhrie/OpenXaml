#pragma once
#include <vector>
#include "XamlObjects/ColumnDefinition.h"
#include "XamlObjects/XamlObject.h"
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