#pragma once
#include "XamlObjects/XamlObject.h"
#include "XamlObjects/RowDefinitionCollection.h"
#include "XamlObjects/ColumnDefinitionCollection.h"
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
		ColumnDefinitionCollection* ColumnDefinitions;
		RowDefinitionCollection* RowDefinitions;
	};
}
