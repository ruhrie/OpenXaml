#pragma once
#include "XamlObjects/XamlObject.h"
#include "XamlObjects/RowDefinition.h"
#include "XamlObjects/ColumnDefinition.h"
#include <vector>
namespace OpenXaml {
	class Grid : public XamlObject
	{
	public:
		void Draw();
		Grid();
		void Initialize();
		void Update();
		~Grid();
		std::vector<RowDefinition*> RowDefinitions;
		std::vector<ColumnDefinition*> ColumnDefinitions;
	};
}
