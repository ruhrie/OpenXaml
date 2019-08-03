#pragma once
#include <vector>
#include "XamlObjects/RowDefinition.h"
#include "XamlObjects/XamlObject.h"
namespace OpenXaml
{
	class RowDefinitionCollection : public XamlObject
	{
	public:
		RowDefinitionCollection();
		~RowDefinitionCollection();
		std::vector<RowDefinition*> Children;
		void Draw();
		void Initialize();
		void Update();
	};
}